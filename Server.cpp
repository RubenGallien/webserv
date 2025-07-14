#include "Server.hpp"


Server::Server(int readSignalFd) : socket(), epoll(readSignalFd, this->socket.getSocketListenerFd())
{
	std::cout << "Server instance created" << std::endl;
}

Server::~Server()
{
	std::cout << "Destroy server instance" << std::endl;
}

bool Server::run()
{
	for (;;)
	{
		if (!this->epoll.actions(this->epoll.wait()))
		{
			close(this->epoll.getEpfd());
			return false;
		}
	}
	return true;
}
