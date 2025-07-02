#include "includes/includes.hpp"

int main()
{
    int socketFD;
    const int port = 8888;
    const std::string addrIp = "127.0.0.1";
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFD == -1)
        std::cout << strerror(errno) << std::endl;

    if (bind(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
        std::cout << strerror(errno) << std::endl;

    
    if (listen(socketFD, 1024) == -1)
         std::cout << strerror(errno) << std::endl;

    close(socketFD);
    return (0);
}