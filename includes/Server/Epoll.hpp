#ifndef EPOLL_HPP
#define EPOLL_HPP

#include <sys/epoll.h>  
#include <sys/socket.h>
#include <fstream>
#include <cstring>
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
        Epoll(const int readSignalFd, int socketListenerFd, ClientManager& clientManager);
        ~Epoll();
        int wait();
        int actions(int nbs);
        int getEpfd();

    private:
        int _readSignalFd;
        int _socketListenerFd;
        ClientManager& _clientManager;
        int _epfd;
        int _acceptFd;
        int epollAccept();
        struct epoll_event _ev;
        struct epoll_event _events[MAX_EVENTS];
};

#endif