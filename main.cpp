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
    
    std::ifstream src("./files/default.html");
    std::string dest;
    std::string line;

    if (src.is_open())
    {
        while (getline(src, line))
            dest += line + '\n';
    }


    socklen_t serverAddressSize = sizeof(serverAddress);

    socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFD == -1)
        std::cout << strerror(errno) << std::endl;

    if (bind(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
        std::cout << strerror(errno) <<  std::endl;

    
    if (listen(socketFD, 1024) == -1)
         std::cout << strerror(errno) << std::endl;


    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        socketAccept = accept(socketFD, (struct sockaddr*)&serverAddress, &serverAddressSize);
        if (socketAccept == -1)
            std::cout << strerror(errno) <<  std::endl;
        if (recv(socketAccept, buffer, 1024, 0))
        {
            std::string result;
            std::ostringstream convert;
            convert << dest.size();
            result = convert.str();
            std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + result + "\r\n"
            "Connection: close\r\n"
            "\r\n" + dest;
            send(socketAccept, response.c_str(), response.size(), 0);
        }
        
    }

    close(socketFD);
    return (0);
}