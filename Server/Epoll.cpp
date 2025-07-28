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
        if (this->_events[i].data.fd == this->_readSignalFd)
            return(0);
        else if (this->_events[i].data.fd == this->_socketListenerFd)
        {
            if (this->epollAccept() == -1)
                return (0);
        }
        else // client want tell something
        {
            if (this->_ev.events == EPOLLIN) // client send a request
            {
                int resp;
                resp = this->_clientManager.showClientRequest(this->_events[i].data.fd);
                std::cout << "bytes receveid = " << resp << std::endl;
                if (!resp)
                    epoll_ctl(this->_epfd, EPOLL_CTL_DEL, this->_events[i].data.fd, &this->_ev);
                else
                {
                    this->_ev.events = EPOLLOUT;
                    epoll_ctl(this->_epfd, EPOLL_CTL_MOD, this->_events[i].data.fd,&this->_ev);
                }
            }
            else if (this->_ev.events == EPOLLOUT) // client is ready to write
            {
                char resp[2048];
                std::string content;
                std::string buffer;

                content.append(
                    "HTTP/1.1 200 OK\nContent-Length: 615\nConnection: close\n\n"
                );
                std::ifstream file ("www/index.html", std::ifstream::in);
                while (std::getline(file, buffer))
                {
                    content.append(buffer);
                    content.append("\n");
                }
                std::cout << content << std::endl;
                std::memcpy(resp, content.c_str(), content.size());
                send(this->_events[i].data.fd, &resp, content.size(), MSG_CONFIRM);
                epoll_ctl(this->_epfd, EPOLL_CTL_DEL, this->_events[i].data.fd, &this->_ev);
                this->_ev.events = EPOLLIN;
                epoll_ctl(this->_epfd, EPOLL_CTL_MOD, this->_events[i].data.fd,&this->_ev);
                file.close();
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