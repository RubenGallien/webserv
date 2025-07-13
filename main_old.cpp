#include "includes/includes.hpp"


int main()
{
    int socketFD;
    sockaddr_in serverAddress = {AF_INET, htons(PORT), {INADDR_ANY}, {0}};


    socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFD == -1)
        std::cout << strerror(errno) << std::endl;

    if (bind(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
        std::cout << strerror(errno) <<  std::endl;

    
    if (listen(socketFD, 1024) == -1)
         std::cout << strerror(errno) << std::endl;

    int epfd = epoll_create1(0);
    if (epfd == -1)
        std::cout << strerror(errno) << std::endl;

    struct epoll_event ev, events[MAX_EVENTS];
    ev.events = EPOLLIN;
    ev.data.fd = socketFD;
    epoll_ctl(epfd, EPOLL_CTL_ADD, socketFD, &ev);

    for (;;)
    {
	int acceptFD;
        int e = epoll_wait(epfd, events, MAX_EVENTS, 30000);
        for (int i = 0; i < e; i++)
        {
		
            if (events[i].data.fd == socketFD)
            {
                std::cout << "new client\n" << std::endl;
                struct sockaddr_in peer_addr;
                socklen_t peer_addr_size = sizeof(peer_addr);
                acceptFD = accept(socketFD, (struct sockaddr*)&peer_addr, &peer_addr_size);
                ev.events = EPOLLIN;
                ev.data.fd = acceptFD;
                epoll_ctl(epfd, EPOLL_CTL_ADD, acceptFD, &ev);
            }
	    else if (events[i].data.fd == acceptFD)
	    {
		    char buffer[1024];
		    int bytesReceived = read(events[i].data.fd, &buffer, 1024);
		    if (bytesReceived > 0)
		    {
			std::cout << buffer << std::endl;
		    }
		    else {
			   std::cout << "Client disconnected" << std::endl;
			   close(events[i].data.fd);
			   epoll_ctl(epfd, EPOLL_CTL_DEL, acceptFD, &ev);
		    }
			

	    }
        }
    }

    close(socketFD);
    return (0);
}
