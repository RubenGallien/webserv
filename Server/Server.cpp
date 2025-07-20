#include "Server.hpp"


Server::Server(int readSignalFd) : 
socket(), 
clientManager(), 
epoll(readSignalFd, this->socket.getSocketListenerFd(), this->clientManager)
{
	std::cout << "Server instance created" << std::endl;
}

/**
* Main loop
 */
bool Server::run()
{
	for (;;)
	{
		// wait an event -> do something when happen
		if (!this->epoll.actions(this->epoll.wait()))
			return false;
	}
	return true;
}

Server::~Server()
{
	close(this->epoll.getEpfd());
	std::cout << "Destroy server instance" << std::endl;
}