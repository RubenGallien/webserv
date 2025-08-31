#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "Client.hpp"
#include "Socket.hpp"
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
        void addClient(int fd, Socket * socket,std::vector<Conf>* confs);
        int manageClientRequest(int fd);
        int responseToClientNow(int fd, HTTPRequest * existingRequest);
        int sendResponse(int target_fd);
        Client * getClient(int fd);
    private:
        std::map<int, Client *> _clients;

};

#endif