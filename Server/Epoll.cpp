#include "Epoll.hpp"

Epoll::Epoll(int readSignalFd, int socketListenerFd, ClientManager& clientManager) : 
readSignalFd(readSignalFd), 
socketListenerFd(socketListenerFd),
clientManager(clientManager)
{
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

int Epoll::wait()
{
    int nbs; 

    nbs = epoll_wait(this->epfd, this->events, MAX_EVENTS, 10000);
    return nbs;
}


int Epoll::epollAccept()
{
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size = sizeof(peer_addr);

    int acceptFd = accept(this->socketListenerFd, (struct sockaddr*)&peer_addr, &peer_addr_size);
    if (acceptFd == -1) {
        std::cout << strerror(errno) << std::endl;
        return -1;
    }
    this->ev.events = EPOLLIN;
    this->ev.data.fd = acceptFd;
    epoll_ctl(this->epfd, EPOLL_CTL_ADD, acceptFd, &this->ev);
    this->clientManager.addClient(acceptFd);
    return (0);
}

int Epoll::actions(int nbs)
{
    for (int i = 0; i < nbs ; i++)
    {
        if (this->events[i].data.fd == this->readSignalFd)
            return(0);
        else if (this->events[i].data.fd == this->socketListenerFd)
        {
            std::cout << "Client want to connect " << std::endl;
            if (this->epollAccept() == -1)
                return (0);
            // this->clientManager.showClients();
        }
        else
        {
            std::cout << "Somemthing happen from " << this->events[i].data.fd << std::endl;
            if (this->ev.events == EPOLLIN)
            {
                std::cout << "He's ready to be read" << std::endl;
                int resp;
                resp = this->clientManager.showClientRequest(this->events[i].data.fd);
                if (!resp)
                    epoll_ctl(this->epfd, EPOLL_CTL_DEL, this->events[i].data.fd, &this->ev);
                else
                {
                    this->ev.events = EPOLLOUT;
                    epoll_ctl(this->epfd, EPOLL_CTL_MOD, this->events[i].data.fd,&this->ev);
                }
            }
            else if (this->ev.events == EPOLLOUT)
            {
                std::cout <<  this->events[i].data.fd << " is ready to be write " << std::endl;
            }

        }
    }
    return (1);
}

int Epoll::getEpfd()
{
    return this->epfd;
}


Epoll::~Epoll()
{
    std::cout << "Epoll instance destroy" << std::endl;
}