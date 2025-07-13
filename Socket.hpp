#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <errno.h>

#define PORT 7988

class Socket {
    
    public:
        Socket();
        ~Socket();
        int getSocketListenerFd();
    private:
        int socketListenerFd;
        sockaddr_in serverAddress;

};