#include "Socket.hpp"

Socket::Socket()
{
    this->socketListenerFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->socketListenerFd == -1)
        std::cout << strerror(errno) << std::endl;


    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(PORT);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (
        bind(
            this->socketListenerFd,
            (struct sockaddr*)&this->serverAddress,
            sizeof(serverAddress)
        ) == -1
    )
        std::cout << strerror(errno) << std::endl;

    if (listen(this->socketListenerFd, 1024) == -1)
        std::cout << strerror(errno) << std::endl;
    

    std::cout << "Socket instance created" << std::endl;
}


int Socket::getSocketListenerFd()
{
    return this->socketListenerFd;
}


Socket::~Socket()
{
    std::cout << "Socket instance destroy" << std::endl;
}