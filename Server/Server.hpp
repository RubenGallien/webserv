#ifndef SERVER_HPP
#define SERVER_HPP

#include "Socket.hpp"
#include "Epoll.hpp"
#include "ClientManager.hpp"
#include <errno.h>
#include <unistd.h>

class Server {
	
	public:
		Server(int readSignalFd);
		~Server();
		bool run();

	private:
		Socket socket;
		ClientManager clientManager;
		Epoll epoll;
};

#endif