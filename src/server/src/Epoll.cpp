#include "Epoll.hpp"

Epoll::Epoll(int readSignalFd, std::vector<Conf> &confs, std::vector<Socket*> &sockets) : 
_readSignalFd(readSignalFd), 
_confs(confs),
_sockets(sockets)
{
    (void)_confs;
    this->_acceptFd = -1;
    this->_epfd = epoll_create1(0);
    if (this->_epfd == -1)
        std::cout << strerror(errno) << std::endl;

    struct epoll_event ev;
    for (size_t i = 0; i < this->_sockets.size(); i++)
    {
        int fd = this->_sockets[i]->getSocketListenerFd();
        ev. events = EPOLLIN;
        ev.data.fd = fd;
        epoll_ctl(this->_epfd, EPOLL_CTL_ADD, fd, &ev);
    }

    ev.data.fd = readSignalFd;
    epoll_ctl(this->_epfd, EPOLL_CTL_ADD, readSignalFd, &ev);

    std::cout << "Epoll parameters instance create" << std::endl;
}

int Epoll::wait()
{
    int nbs; 

    nbs = epoll_wait(this->_epfd, this->_events, MAX_EVENTS, 10000);
    return nbs;
}

void Epoll::handleClientEvent(int target_fd, int event)
{
    switch (event)
    {
        case EPOLLIN:
            std::cout << "[EPOLLIN]" << std::endl;
            if (!this->_clientManager.manageClientRequest(target_fd))
                epoll_ctl(this->_epfd, EPOLL_CTL_DEL, target_fd, NULL);
            else if (this->_clientManager.getClient(target_fd)->getRdyToWrite())
            {
                struct epoll_event ev;
                ev.events = EPOLLOUT;
                ev.data.fd = target_fd;
                epoll_ctl(this->_epfd, EPOLL_CTL_MOD, target_fd, &ev);
            }
            break;
        case EPOLLOUT:
            std::cout << "[EPOLLOUT]" << std::endl;
            std::cout << "Je suis pret a recevoir une reponse" << std::endl;
            this->_clientManager.sendResponse(target_fd);
            exit(0);
            break;
        default:
            std::cout << "ni EPOLLIN ni EPOLLOUT" << std::endl;
            break;
    }
}

int Epoll::epollAccept(int target_fd)
{
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size = sizeof(peer_addr);

    int acceptFd = accept(target_fd, (struct sockaddr*)&peer_addr, &peer_addr_size);
    if (acceptFd == -1) {
        std::cout << strerror(errno) << std::endl;
        return -1;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = acceptFd;
    epoll_ctl(this->_epfd, EPOLL_CTL_ADD, acceptFd, &ev);
    this->_clientManager.addClient(acceptFd, this->findSocket(target_fd), &this->_confs);
    return (0);
}

int Epoll::actions(int nbs)
{
    for (int i = 0; i < nbs ; i++)
    {
        int target_fd = this->_events[i].data.fd;
        if (target_fd == this->_readSignalFd)
            return(this->_clientManager.~ClientManager(),0);
        else if (this->targetIsListenerFd(target_fd))
        {
            if (this->epollAccept(target_fd) == -1)
                continue;
        }
        else
            this->handleClientEvent(target_fd, this->_events[i].events);
    }
    return (1);
}


Socket * Epoll::findSocket(int fd)
{
    for (std::vector<Socket*>::iterator it = this->_sockets.begin() ; it != this->_sockets.end(); ++it)
    {
        if ((*it)->getSocketListenerFd() == fd)
            return *it;
    }
    return NULL;
}

int Epoll::getEpfd()
{
    return this->_epfd;
}

int Epoll::targetIsListenerFd(int target)
{
    for (size_t i = 0; i < this->_sockets.size(); i++)
    {
        if (target == this->_sockets[i]->getSocketListenerFd())
            return (1);
    }
    return (0);
}

Epoll::~Epoll()
{
    std::cout << "Epoll instance destroy" << std::endl;
}