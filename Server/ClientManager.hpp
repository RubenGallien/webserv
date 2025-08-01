#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "Client.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
#include <map>
#include <stdlib.h>

#include <sys/socket.h>

class ClientManager {
    public:
        ClientManager();
        ~ClientManager();
        void addClient(int fd);
        int manageClientRequest(int fd);
        void showClients();
        Client * getClient(int fd);
    private:
        std::map<int, Client *> _clients;

};

#endif