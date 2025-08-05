#include "includes/includes.hpp"
#include "Server/Server.hpp"
#include "Utils/Signal.hpp"
#include "Server/HTTPRequest.hpp"

int main()
{

	Signal signal;
	Server *server = new Server(signal.getReadFd());

	server->run();

	delete server;
}
