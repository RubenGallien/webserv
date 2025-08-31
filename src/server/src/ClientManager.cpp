#include "ClientManager.hpp"

ClientManager::ClientManager()
{
    std::cout << "ClientManager instance created at " << this << std::endl;
}

void ClientManager::addClient(int fd, Socket * socket, std::vector<Conf>* confs)
{
    Client * client = new Client(fd);

    int i = 0;
    for (std::vector<Conf>::iterator it = confs->begin(); it != confs->end(); ++it)
    {
        if (it->getHost() == socket->getHost() && it->getPort() == socket->getPort())
        {
            i++;
            client->_confs.pushBack(*it);
        }
    }
    std::cout << "I have add " << i << " diff conf : " << std::endl;
    this->_clients[fd] = client;
}

int ClientManager::manageClientRequest(int fd)
{
    std::cout << "manage ma requete, je suis " << fd << std::endl;
    char buffer[1024];
    int bytes = recv(fd, &buffer, 1024, 0);
    buffer[bytes] = '\0';


    if (!bytes)
        return (this->_clients.erase(fd), close(fd), 0);

    Client * client = this->getClient(fd);
    HTTPRequest * existingRequest = client->getReq();
    if (!existingRequest)
    {
        client->setReq(buffer, bytes);
        existingRequest = client->getReq();
    }
    else
        existingRequest->extend(buffer, bytes);
    size_t initialBytes = existingRequest->getBytes() - bytes;
    existingRequest->fastParsing(initialBytes);
    if (existingRequest->responseNow())
        return (this->responseToClientNow(fd, existingRequest));
    else if(existingRequest->hasReadyToPrepare())
        client->setRdyToWrite(1);
    return (1);
}

int ClientManager::responseToClientNow(int fd, HTTPRequest * existingRequest)
{

    std::cout << "Voici ce que je vais repondre au client: \n" << std::endl; 
    std::string response = existingRequest->getResponse();

    std::cout << response << std::endl;

    send(fd, response.c_str(), response.size(), 0);
    std::map<int, Client*>::iterator it = this->_clients.find(fd);
    if (it != this->_clients.end())
    {
        delete it->second;
        this->_clients.erase(it);
    }
    close(fd);
    return (0);
}

int ClientManager::sendResponse(int target_fd)
{
    Client * client = this->getClient(target_fd);
    HTTPRequest * existingRequest = client->getReq();
    std::string response = existingRequest->getResponse();
    send(target_fd, response.c_str(), response.size(), 0);
    return 1;
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