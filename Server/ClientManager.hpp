#include <string>
#include <iostream>
#include <map>
#include <./Client.hpp>

class ClientManager {
    public:
        ClientManager();
        ~ClientManager();

    private:
        std::map<int, Client> clients;

};