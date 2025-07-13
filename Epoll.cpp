#include "Epoll.hpp"

Epoll::Epoll(int readSignalFd, int socketListenerFd) : readSignalFd(readSignalFd), socketListenerFd(socketListenerFd)
{
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

int Epoll::actions(int nbs)
{
    for (int i = 0; i < nbs ; i++)
    {
        if (this->events[i].data.fd == this->readSignalFd)
        {
            epoll_ctl(this->epfd, EPOLL_CTL_DEL, this->readSignalFd, NULL);
            epoll_ctl(this->epfd, EPOLL_CTL_DEL, this->socketListenerFd, NULL);
            return(0);
        }

    }

    return (1);
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