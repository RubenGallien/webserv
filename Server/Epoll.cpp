#include "Epoll.hpp"

Epoll::Epoll(int readSignalFd, int socketListenerFd, ClientManager& clientManager) : 
_readSignalFd(readSignalFd), 
_socketListenerFd(socketListenerFd),
_clientManager(clientManager)
{
    this->_acceptFd = -1;
    this->_epfd = epoll_create1(0);
    if (this->_epfd == -1)
        std::cout << strerror(errno) << std::endl;

    this->_ev.events = EPOLLIN;
    this->_ev.data.fd = socketListenerFd;
    epoll_ctl(this->_epfd, EPOLL_CTL_ADD, socketListenerFd, &_ev);

    this->_ev.data.fd = readSignalFd;
    epoll_ctl(this->_epfd, EPOLL_CTL_ADD, readSignalFd, &_ev);

    std::cout << "Epoll parameters instance create" << std::endl;
}

int Epoll::wait()
{
    int nbs; 

    nbs = epoll_wait(this->_epfd, this->_events, MAX_EVENTS, 10000);
    return nbs;
}


int Epoll::epollAccept()
{
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size = sizeof(peer_addr);

    int acceptFd = accept(this->_socketListenerFd, (struct sockaddr*)&peer_addr, &peer_addr_size);
    if (acceptFd == -1) {
        std::cout << strerror(errno) << std::endl;
        return -1;
    }
    this->_ev.events = EPOLLIN;
    this->_ev.data.fd = acceptFd;
    epoll_ctl(this->_epfd, EPOLL_CTL_ADD, acceptFd, &this->_ev);
    this->_clientManager.addClient(acceptFd);
    return (0);
}

int Epoll::actions(int nbs)
{
    for (int i = 0; i < nbs ; i++)
    {
        int target_fd = this->_events[i].data.fd;
        if (target_fd == this->_readSignalFd)
            return(0);
        else if (target_fd == this->_socketListenerFd)
        {
            if (this->epollAccept() == -1)
                return (0);
        }
        else
        {
            switch (this->_ev.events)
            {
                case EPOLLIN:
                    if (!this->_clientManager.manageClientRequest(target_fd))
                        epoll_ctl(this->_epfd, EPOLL_CTL_DEL, target_fd, &this->_ev);
                    break;
                case EPOLLOUT:
                        /* code*/
                default:
                    std::cout << "ni EPOLLIN ni EPOLLOUT" << std::endl;
            }
        }
    }
    return (1);
}

int Epoll::getEpfd()
{
    return this->_epfd;
}


Epoll::~Epoll()
{
    std::cout << "Epoll instance destroy" << std::endl;
}