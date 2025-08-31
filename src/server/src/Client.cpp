#include "Client.hpp"

Client::Client()
{
    std::cout << "default client constructor" << std::endl;
}

Client::Client(int fd)
{
    this->fd = fd;
    std::cout << "Wow a new client happens with fd : " << this->fd << std::endl;
}

Client::Client(const Client& other)
{
    *this = other;
    return;
}


Client& Client::operator=(const Client& src)
{
    this->_fd = src._fd;
    this->_buffer = src._buffer;
    this->_requests = src._requests;
    this->_confs = src._confs;
    return *this;
}

Client::~Client()
{
    std::cout << "A client leave the room" << std::endl;
}