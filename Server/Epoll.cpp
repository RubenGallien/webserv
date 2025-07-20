#include "Epoll.hpp"

Epoll::Epoll(int readSignalFd, int socketListenerFd, ClientManager& clientManager) : 
readSignalFd(readSignalFd), 
socketListenerFd(socketListenerFd),
clientManager(clientManager)
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

    this->acceptFd = accept(this->socketListenerFd, (struct sockaddr*)&peer_addr, &peer_addr_size);
    if (this->acceptFd == -1) {
        std::cout << strerror(errno) << std::endl;
        return -1;
    }
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &peer_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    std::cout << "Connexion acceptée de " << client_ip << ":" << ntohs(peer_addr.sin_port) << std::endl;
    this->ev.events = EPOLLIN;
    this->ev.data.fd = this->acceptFd;
    epoll_ctl(this->epfd, EPOLL_CTL_ADD, this->acceptFd, &this->ev);
    this->allFds.push_back(acceptFd);
    this->clientManager.addClient(this->acceptFd);
    return (0);
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
        {
            std::cout << "Événement sur socket listener (connexion entrante)" << std::endl;
            if (this->epollAccept() == -1)
                return (0);
            this->clientManager.showClients();
        }
    }
    return (1);
}

// int Epoll::actions(int nbs)
// {
//     for (int i = 0; i < nbs ; i++)
//     {
//         if (this->events[i].data.fd == this->readSignalFd)
//         {
//             this->ft_close();
//             return(0);
//         }
//         else if (this->events[i].data.fd == this->socketListenerFd)
//             this->epollAccept();
//         else if (this->acceptFd > 0 && this->events[i].data.fd == this->acceptFd)
//         {
//             char buffer[1024];
//             int bytesReceveid = read(this->events[i].data.fd, &buffer, 1024);
//             buffer[bytesReceveid] = '\0';
//             if (bytesReceveid)
//                 std::cout << this->events[i].data.fd << ":\n" << buffer << std::endl;
//             else
//             {
//                 std::cout << this->events[i].data.fd << " disconnected" << std::endl;
//                 close(this->events[i].data.fd);
//                 epoll_ctl(this->epfd, EPOLL_CTL_DEL, this->acceptFd, &this->ev);
//             }
//         }
//     }
//     return (1);
// }

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


Epoll::~Epoll()
{
    std::cout << "Epoll instance destroy" << std::endl;
}