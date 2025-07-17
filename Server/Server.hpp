#include "Socket.hpp"
#include "Epoll.hpp"
#include <errno.h>
#include <unistd.h>

class Server {
	
	public:
		Server(int readSignalFd);
		~Server();
		bool run();

	private:
		Socket socket;
		Epoll epoll;

};
