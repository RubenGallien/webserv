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

void ClientManager::manageRequest(int fd)
{
    char buffer[1024];
    int bytes = recv(fd, &buffer, 1024, 0);
    if (!this->_clients[fd]->getReq() && bytes)
    {
        HTTPRequest * newRequest = new HTTPRequest(buffer);
        this->_clients[fd]->setReq(newRequest);
    }
}

// int ClientManager::showClientRequest(int fd)
// {
//     char buffer[1024];
    
//     int clientfd = this->_clients[fd]->getFd();
//     int bytes = recv(clientfd, &buffer, 1024, 0);
//     if (bytes)
//         std::cout << buffer << std::endl;
//     else
//         return (0);
//     return (1);
// }


ClientManager::~ClientManager()
{
    for (std::map<int, Client*>::iterator it=this->_clients.begin(); it != this->_clients.end(); ++it)
    {
        close(it->second->getFd());
        delete it->second;
    }
    std::cout << "ClientManager instance destroy" << std::endl;
}