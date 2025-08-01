#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest()
{
    return;
}

HTTPRequest::HTTPRequest(std::string req, size_t bytes)
{
    std::cout << req << std::endl;
    this->_bytesBuffer = bytes;
    this->_buffer = req;
    std::cout << "Create an HTTP Request" << std::endl;
}

int HTTPRequest::hasReadyToPrepare()
{
    if(this->_buffer.find("\r\n\r\n") == std::string::npos)
        return -1;
    return 1;

}

void HTTPRequest::extend(std::string buffer, size_t bytes)
{
    this->_buffer += buffer;
    this->_bytesBuffer += bytes;
}

std::string HTTPRequest::getBuffer()
{
    return this->_buffer;
}

HTTPRequest::~HTTPRequest()
{
    
}