#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <string>
#include <iostream>
#include <unistd.h>
#include <map>
#include <stdlib.h>
#include <sys/socket.h>

#include "Client.hpp"
#include "Socket.hpp"
#include "HTTPRequestParser.hpp"

class ClientManager {
    public:
        ClientManager();
        ~ClientManager();
        void addClient(int fd, Socket * socket,std::vector<Conf>* confs);
        void receiveData(int fd);
        Client * getClient(int fd);
    private:
        std::map<int, Client *> _clients;

};

#endif