#ifndef HTTPREQUEST
#define HTTPREQUEST

#include <iostream>
#include <string>
#include <map>
#include <sstream>


class HTTPRequest 
{

    private:
        std::string _method;
        std::string _path;
        std::string _version;
        std::map<std::string, std::string> _fields;
    public:
        HTTPRequest();
        HTTPRequest(std::string req);
        ~HTTPRequest();

};

#endif