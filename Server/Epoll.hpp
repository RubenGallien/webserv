#include <sys/epoll.h>  
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#define MAX_EVENTS 10

class Epoll {

    public:
        Epoll();
        Epoll(int readSignalFd, int socketListenerFd);
        ~Epoll();
        int wait();
        int actions(int nbs);
        int getEpfd();

    private:
        std::vector<int>allFds;
        int epfd;
        int readSignalFd;
        int socketListenerFd;
        int acceptFd;
        int epollAccept();
        void ft_close();
        struct epoll_event ev;
        struct epoll_event events[MAX_EVENTS];
};