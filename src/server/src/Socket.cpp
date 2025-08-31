#include "Socket.hpp"

Socket::Socket()
{
    std::cout << "Socket instance created" << std::endl;
    return;
}

Socket::Socket(Conf conf)
{
    this->_serverAddress = NULL;
    struct addrinfo hints;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    std::string host = conf.getHost();
    std::string port = conf.getPort();

    int i = getaddrinfo(host.c_str(), port.c_str(), &hints, &this->_serverAddress);
    if (i != 0)
        std::cout << gai_strerror(i) << std::endl;
    this->_host = host;
    this->_port = port;
    std::cout << "Socket parametric instance created" << std::endl;
}

void Socket::listen()
{
    if (::listen(this->_socketListenerFd, 1024) == -1)
        std::cout << strerror(errno) << std::endl;
}

void Socket::createAndBind()
{
    struct addrinfo *rp;
    for (rp = this->_serverAddress; rp != NULL; rp = rp->ai_next)
    {
        this->_socketListenerFd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (this->_socketListenerFd == -1)
            continue;

        if (bind(this->_socketListenerFd, rp->ai_addr, rp->ai_addrlen) == 0)
        {
            struct sockaddr_in my_addr;
            char myIP[16];
            unsigned int myPort;
            bzero(&my_addr, sizeof(my_addr));
            socklen_t len = sizeof(my_addr);
            getsockname(this->_socketListenerFd, (struct sockaddr *) &my_addr, &len);
            inet_ntop(AF_INET, &my_addr.sin_addr, myIP, sizeof(myIP));
            myPort = ntohs(my_addr.sin_port);
            std::cout << "bind FD[" << this->_socketListenerFd << "]" << " on :  ";
            std::cout << myIP;
            std::cout << ":" << myPort << std::endl;
            break;
        }

        close(this->_socketListenerFd);
    }
}

int Socket::getSocketListenerFd()
{
    return this->_socketListenerFd;
}

std::string Socket::getHost()
{
    return this->_host;
}

std::string Socket::getPort()
{
    return this->_port;
}

Socket::~Socket()
{

    std::cout << "Socket "<< this->_socketListenerFd << " instance destroy : " << std::endl;
    if (this->_serverAddress) {
        close(this->_socketListenerFd);
        freeaddrinfo(this->_serverAddress);
    }
}