#ifndef EPOLL_HPP
#define EPOLL_HPP

#include <sys/epoll.h>  
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "ClientManager.hpp"
#include <arpa/inet.h>

#define MAX_EVENTS 10

class Epoll {

    public:
        Epoll(int readSignalFd, int socketListenerFd, ClientManager& clientManager);
        ~Epoll();
        int wait();
        int actions(int nbs);
        int getEpfd();

    private:
        int readSignalFd;
        int socketListenerFd;
        ClientManager& clientManager;
        std::vector<int>allFds;
        int epfd;
        int acceptFd;
        int epollAccept();
        void ft_close();
        struct epoll_event ev;
        struct epoll_event events[MAX_EVENTS];
};

#endif