#ifndef HTTPREQUEST
#define HTTPREQUEST

#include <iostream>
#include <string>
#include <map>
#include <sstream>


class HTTPRequest 
{

    private:
        size_t  _bytesBuffer;
        size_t  _contentLength;
        size_t  _transferEncoding;
        size_t  _endHeader;
        std::string _buffer;
        
    public:
        HTTPRequest();
        HTTPRequest(std::string req, size_t bytes);
        void extend(std::string buffer, size_t bytes);
        int hasReadyToPrepare();
        void isChunkedComplete();
        // void isBodyCorrespondLength();
        std::string getBuffer();
        ~HTTPRequest();

};

#endif