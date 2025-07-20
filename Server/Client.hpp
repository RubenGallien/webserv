#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
    public:
        Client();
        Client(int fd);
        ~Client();

    private:
        int fd;

};

#endif