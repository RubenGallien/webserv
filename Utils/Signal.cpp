#include "Signal.hpp"

int g_writePipeFd = -1;

Signal::Signal()
{
	pipe(this->pipeFd);
	this->readPipeFd = this->pipeFd[0];
	this->writePipeFd = this->pipeFd[1];
	init_signal(this->writePipeFd);
	std::cout << "Signal instance created" << std::endl; 
}


void signal_handler(int signal)
{
	if (signal == 2)
	{
		write(g_writePipeFd, "2", 1);
	}
}

void Signal::closePipe()
{
	close(this->writePipeFd);
	close(this->readPipeFd);
}

void Signal::init_signal(int writeFd)
{
	g_writePipeFd = writeFd;
	std::signal(SIGINT, signal_handler);
}

int Signal::getReadFd()
{
	return this->readPipeFd;
}

Signal::~Signal()
{
	std::cout << "Destroy Signal instance" << std::endl;
}