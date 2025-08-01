#ifndef HTTPREQUEST
#define HTTPREQUEST

#include <iostream>
#include <string>
#include <map>
#include <sstream>


class HTTPRequest 
{

    private:
        size_t      _bytesBuffer;
        std::string _buffer;
        std::string _method;
        std::string _path;
        std::string _version;
        std::map<std::string, std::string> _fields;
    public:
        HTTPRequest();
        HTTPRequest(std::string req, size_t bytes);
        void extend(std::string buffer, size_t bytes);
        int hasReadyToPrepare();
        std::string getBuffer();
        ~HTTPRequest();

};

#endif