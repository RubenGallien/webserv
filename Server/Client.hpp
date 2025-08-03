#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "HTTPRequest.hpp"


class Client
{
    public:
        Client();
        Client(int fd);
        ~Client();
        int getFd();
        int getRdyToWrite();
        void setRdyToWrite(int value);
        HTTPRequest * getReq();
        void setReq(std::string buffer, size_t bytes);
    private:
        int rdyToWrite;
        int fd;
        HTTPRequest * _req;

};

#endif