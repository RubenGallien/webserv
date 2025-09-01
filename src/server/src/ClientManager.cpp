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
            client->setConf(*it);
        }
    }
    this->_clients[fd] = client;
}

void ClientManager::receiveData(int fd)
{
    char buffer[1024];
    size_t bytes = recv(fd, &buffer, 1024, 0);
    buffer[bytes] = '\0';

    Client * client = this->getClient(fd);

    /*
    * Client disconnect properly
    */
    // if (!bytes)
    //     return;

    client->setBuffer(buffer);
    if (!client->hasRequests() || client->lastRequestComplete())
        client->startNewRequest();

    HTTPRequestParser::fillRequest(client->getRequest(), client->getBuffer());

    if (client->getRequest().complete == true)
        exit(0);

    return;
}

// int ClientManager::manageClientRequest(int fd)
// {
//     std::cout << "manage ma requete, je suis " << fd << std::endl;
//     char buffer[1024];
//     int bytes = recv(fd, &buffer, 1024, 0);
//     buffer[bytes] = '\0';


//     if (!bytes)
//         return (this->_clients.erase(fd), close(fd), 0);

//     Client * client = this->getClient(fd);
//     HTTPRequest * existingRequest = client->getReq();
//     if (!existingRequest)
//     {
//         client->setReq(buffer, bytes);
//         existingRequest = client->getReq();
//     }
//     else
//         existingRequest->extend(buffer, bytes);
//     size_t initialBytes = existingRequest->getBytes() - bytes;
//     existingRequest->fastParsing(initialBytes);
//     if (existingRequest->responseNow())
//         return (this->responseToClientNow(fd, existingRequest));
//     else if(existingRequest->hasReadyToPrepare())
//         client->setRdyToWrite(1);
//     return (1);
// }

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