#include "Epoll.hpp"

Epoll::Epoll(int readSignalFd, int socketListenerFd) : readSignalFd(readSignalFd), socketListenerFd(socketListenerFd)
{
    this->allFds.push_back(this->readSignalFd);
    this->allFds.push_back(this->socketListenerFd);
    this->acceptFd = -1;
    this->epfd = epoll_create1(0);
    if (this->epfd == -1)
        std::cout << strerror(errno) << std::endl;

    this->ev.events = EPOLLIN;
    this->ev.data.fd = socketListenerFd;
    epoll_ctl(this->epfd, EPOLL_CTL_ADD, socketListenerFd, &ev);

    this->ev.data.fd = readSignalFd;
    epoll_ctl(this->epfd, EPOLL_CTL_ADD, readSignalFd, &ev);

    std::cout << "Epoll parameters instance create" << std::endl;
}

int Epoll::epollAccept()
{
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size = sizeof(peer_addr);
    this->acceptFd = accept(this->socketListenerFd, (struct sockaddr*)&peer_addr, &peer_addr_size);
    ev.events = EPOLLIN;
    ev.data.fd = this->acceptFd;
    epoll_ctl(this->epfd, EPOLL_CTL_ADD, this->acceptFd, &ev);
    this->allFds.push_back(acceptFd);
    return (0);
}


int Epoll::wait()
{
    int nbs; 

    nbs = epoll_wait(this->epfd, this->events, MAX_EVENTS, 10000);
    return nbs;
}

int Epoll::actions(int nbs)
{
    for (int i = 0; i < nbs ; i++)
    {
        if (this->events[i].data.fd == this->readSignalFd)
        {
            this->ft_close();
            return(0);
        }
        else if (this->events[i].data.fd == this->socketListenerFd)
            this->epollAccept();
        else if (this->acceptFd > 0 && this->events[i].data.fd == this->acceptFd)
        {
            char buffer[1024];
            int bytesReceveid = read(this->events[i].data.fd, &buffer, 1024);
            buffer[bytesReceveid] = '\0';
            if (bytesReceveid)
                std::cout << this->events[i].data.fd << ":\n" << buffer << std::endl;
            else
            {
                close(this->events[i].data.fd);
                epoll_ctl(this->epfd, EPOLL_CTL_DEL, this->acceptFd, &this->ev);
            }
        }
    }
    return (1);
}

void Epoll::ft_close()
{
    for (unsigned int i = 0; i < this->allFds.size(); i++)
    {
        epoll_ctl(this->epfd, EPOLL_CTL_DEL, this->allFds[i], NULL);
        close(this->allFds[i]);
    }
}

int Epoll::getEpfd()
{
    return this->epfd;
}

Epoll::Epoll()
{
    std::cout << "Epoll instance create" << std::endl;
}

Epoll::~Epoll()
{
    std::cout << "Epoll instance destroy" << std::endl;
}