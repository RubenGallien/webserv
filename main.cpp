#include "includes/includes.hpp"


int main()
{
    int socketFD;
    sockaddr_in serverAddress = {AF_INET, htons(PORT), {INADDR_ANY}, {0}};
    // char buffer[1024];
    
    std::ifstream src("./files/default.html");
    std::string dest;
    std::string line;

    if (src.is_open())
    {
        while (getline(src, line))
            dest += line + '\n';
    }

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
        int ev_happened = epoll_wait(epfd, events, MAX_EVENTS, 30000);
        std::cout << ev_happened << std::endl;
        for (int i; i < ev_happened; i++)
        {
            if (events[i].data.fd == socketFD)
            {
                int acceptFD;
                struct sockaddr_in peer_addr;
                socklen_t peer_addr_size = sizeof(peer_addr);
                acceptFD = accept(socketFD, (struct sockaddr*)&peer_addr, &peer_addr_size);
                
            }
        }
    }

    close(socketFD);
    return (0);
}