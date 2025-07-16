#include "./includes/includes.hpp"
#include "./Server.hpp"
#include "./Utils/Signal.hpp"


int main()
{

	Signal signal;
	Server *server = new Server(signal.getReadFd());

	server->run();

	delete server;
}
