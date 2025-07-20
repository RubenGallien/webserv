#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "Client.hpp"
#include <string>
#include <iostream>
#include <map>
#include <stdlib.h>

class ClientManager {
    public:
        ClientManager();
        ~ClientManager();
        void addClient(int fd);
        void showClients();
    private:
        std::map<int, Client> clients;

};

#endif