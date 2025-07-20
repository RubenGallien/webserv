#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "../includes/includes.hpp"
#include <csignal>


class Signal {
	
	private:
		int pipeFd[2];
		int writePipeFd;
		int readPipeFd;

	public:
		Signal();
		~Signal();
		void init_signal(int writeFd);
		int getReadFd();
	
};

#endif