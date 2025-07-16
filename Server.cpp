#include "Server.hpp"


Server::Server(int readSignalFd) : socket(), epoll(readSignalFd, this->socket.getSocketListenerFd())
{
	std::cout << "Server instance created" << std::endl;
}

bool Server::run()
{
	for (;;)
	{
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