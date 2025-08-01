#include "./ClientManager.hpp"

ClientManager::ClientManager()
{
    std::cout << "ClientManager instance created" << std::endl;
}

void ClientManager::addClient(int fd)
{
    Client * client = new Client(fd);
    this->_clients[fd] = client;
}

void ClientManager::showClients()
{
    std::cout << "There is " << this->_clients.size() << " clients:" << std::endl;
    for (std::map<int, Client*>::iterator it=this->_clients.begin(); it != this->_clients.end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
}

int ClientManager::manageClientRequest(int fd)
{
    char buffer[1024];
    int bytes = recv(fd, &buffer, 1024, 0);
    buffer[bytes] = '\0';

    if (!bytes)
        return (std::cout << fd << " leave " << std::endl, close(fd), 0);
    
    Client * client = this->getClient(fd);
    HTTPRequest * existingRequest = client->getReq();
    if (!existingRequest)
    {
        client->setReq(buffer, bytes);
        existingRequest = client->getReq();
    }
    else
        existingRequest->extend(buffer, bytes);
    std::cout << existingRequest->hasReadyToPrepare() << std::endl;
    return (1);
}

Client * ClientManager::getClient(int fd)
{
    return this->_clients[fd];
}


ClientManager::~ClientManager()
{
    for (std::map<int, Client*>::iterator it=this->_clients.begin(); it != this->_clients.end(); ++it)
    {
        close(it->second->getFd());
        delete it->second;
    }
    std::cout << "ClientManager instance destroy" << std::endl;
}