#include "./Client.hpp"

Client::Client()
{
    std::cout << "default client constructor" << std::endl;
}

Client::Client(int fd)
{
    this->fd = fd;
    this->_req = NULL;
    std::cout << "Wow a new client happens" << std::endl;
}

int Client::getFd()
{
    return this->fd;
}

void Client::setReq(std::string buffer, size_t bytes)
{
    HTTPRequest * newRequest = new HTTPRequest(buffer, bytes);
    this->_req = newRequest;
}

HTTPRequest * Client::getReq()
{
    return this->_req;
}

Client::~Client()
{
    delete this->_req;
    std::cout << "A client leave the room" << std::endl;
}