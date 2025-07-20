#include "./ClientManager.hpp"

ClientManager::ClientManager()
{
    std::cout << "ClientManager instance created" << std::endl;
}

void ClientManager::addClient(int fd)
{
    this->clients[fd] = Client(fd);
}

void ClientManager::showClients()
{
    std::cout << "There is " << this->clients.size() << " clients:" << std::endl;
    for (std::map<int, Client>::iterator it=this->clients.begin(); it != this->clients.end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
    // exit(0);
}

ClientManager::~ClientManager()
{
    std::cout << "ClientManager instance destroy" << std::endl;
}