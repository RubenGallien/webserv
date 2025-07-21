#include "./ClientManager.hpp"

ClientManager::ClientManager()
{
    std::cout << "ClientManager instance created" << std::endl;
}

void ClientManager::addClient(int fd)
{
    Client * client = new Client(fd);
    this->clients[fd] = client;
}

void ClientManager::showClients()
{
    std::cout << "There is " << this->clients.size() << " clients:" << std::endl;
    for (std::map<int, Client*>::iterator it=this->clients.begin(); it != this->clients.end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
}

int ClientManager::showClientRequest(int fd)
{
    char buffer[1024];
    
    int clientfd = this->clients[fd]->getFd();
    int bytes = recv(clientfd, &buffer, 1024, 0);
    if (bytes)
        std::cout << buffer << std::endl;
    else
        return (0);
    return (1);
}


ClientManager::~ClientManager()
{
    for (std::map<int, Client*>::iterator it=this->clients.begin(); it != this->clients.end(); ++it)
    {
        close(it->second->getFd());
        delete it->second;
    }
    std::cout << "ClientManager instance destroy" << std::endl;
}