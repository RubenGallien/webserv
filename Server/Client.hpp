#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
    public:
        Client();
        Client(int fd);
        ~Client();
        int getFd();
    private:
        int fd;

};

#endif