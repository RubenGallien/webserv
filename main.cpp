#include "includes/includes.hpp"

int main()
{
    int socketFD, socketAccept;
    const int port = 8888;
    const std::string addrIp = "127.0.0.1";
    sockaddr_in serverAddress;
    char buffer[1024];
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    socklen_t serverAddressSize = sizeof(serverAddress);

    socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFD == -1)
        std::cout << strerror(errno) << " 18 " << std::endl;

    if (bind(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
        std::cout << strerror(errno) << " 21 " <<  std::endl;

    
    if (listen(socketFD, 1024) == -1)
         std::cout << strerror(errno) << " 25 " << std::endl;


    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        socketAccept = accept(socketFD, (struct sockaddr*)&serverAddress, &serverAddressSize);
        if (socketAccept == -1)
            std::cout << strerror(errno) << " 33 " << std::endl;
        recv(socketAccept, buffer, 1024, 0);
        std::cout << buffer << std::endl;
        
    }

    close(socketFD);
    return (0);
}