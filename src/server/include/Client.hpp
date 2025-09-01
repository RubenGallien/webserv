#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "HTTPRequest.hpp"
#include "Conf.hpp"

class Client
{
    private:
        int                      _fd;
        std::string              _buffer;
        std::vector<HTTPRequest> _requests;
        std::vector<Conf>        _confs;

    public:
        Client();
        Client(int fd);
        Client(const Client& other);

        Client& operator=(const Client& src);

        
        // getter
        int getFd();
        std::string& getBuffer();
        HTTPRequest & getRequest();
        std::vector<HTTPRequest>& getAllRequest();


        // setter
        void setConf(Conf & conf);
        void setBuffer(std::string data);

        // requests
        int hasRequests();
        int lastRequestComplete();
        void startNewRequest();
        void addRequest(HTTPRequest & newRequest);

        ~Client();

};

#endif