#include "Client.hpp"

Client::Client()
{
    std::cout << "default client constructor" << std::endl;
}

Client::Client(int fd)
{
    this->_fd = fd;
    std::cout << "Wow a new client happens with fd : " << this->_fd << std::endl;
}

Client::Client(const Client& other)
{
    *this = other;
    return;
}

int Client::getFd()
{
    return this->_fd;
}

std::string& Client::getBuffer()
{
    return this->_buffer;
}

void Client::setConf(Conf & conf)
{
    this->_confs.push_back(conf);
}

void Client::setBuffer(std::string data)
{
    this->_buffer += data;
}

int Client::hasRequests()
{
    return this->_requests.size();
}

int Client::lastRequestComplete()
{
    return this->_requests.back().complete;
}

void Client::startNewRequest()
{
    this->_requests.push_back(HTTPRequest());
}

HTTPRequest & Client::getRequest()
{
    return this->_requests.back();
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