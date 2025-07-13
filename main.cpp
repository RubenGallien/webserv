#include "./includes/includes.hpp"
#include "./Server.hpp"
#include "./Utils/Signal.hpp"


int main()
{

	return (0);

	Signal signal;
	Server *server = new Server(signal.getReadFd());

	if (!server->run())
		signal.closePipe();

	delete server;
}
