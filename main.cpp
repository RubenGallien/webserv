#include "includes/includes.hpp"

int main()
{
    int socketFD;
    const int port = 8888;
    const std::string addrIp = "127.0.0.1";

    socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFD == -1)
        std::cout << strerror(errno) << std::endl;
    if (listen(socketFD, 1024) == -1)
         std::cout << strerror(errno) << std::endl;
    
    
    close(socketFD);

}