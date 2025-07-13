#include <sys/epoll.h>  
#include <string.h>
#include <iostream>
#include <errno.h>

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
        int epfd;
        int readSignalFd;
        int socketListenerFd;
        struct epoll_event ev;
        struct epoll_event events[MAX_EVENTS];
};