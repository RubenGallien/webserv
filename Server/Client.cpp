#include "./Client.hpp"

Client::Client()
{
    std::cout << "default client constructor" << std::endl;
}

Client::Client(int fd)
{
    this->fd = fd;
    std::cout << "Wow a new client happens" << std::endl;
}

Client::~Client()
{
    std::cout << "A client leave the room" << std::endl;
}