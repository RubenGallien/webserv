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
    this->_endHeader = this->_buffer.find("\r\n\r\n");
    if(this->_endHeader == std::string::npos)
        return 0;
    this->_contentLength =  this->_buffer.find("Content-Length");
    this->_transferEncoding = this->_buffer.find("Transfer-Encoding: chunked");
    if (this->_contentLength == std::string::npos 
        && this->_transferEncoding == std::string::npos)
        return 1;
    if (this->_transferEncoding)
        this->isChunkedComplete();
    // else if (this->_contentLength)
    //     this->isBodyCorrespondLength();
    if (this->_transferEncoding || this->_contentLength)
        return 1;
    return 0;

}

void HTTPRequest::isChunkedComplete()
{
    size_t pos = this->_endHeader + 4;

    while (true)
    {
        size_t endline = this->_buffer.find("\r\n", pos);

        if (endline == std::string::npos)
            return;

        std::string lenStr = this->_buffer.substr(pos, endline);

        int len;
        std::istringstream(lenStr) >> len;

        pos += endline + 2;
        if (len == 0)
        {
            if (this->_buffer.size() >= pos + 2 && this->_buffer.substr(pos, 2) == "\r\n")
                this->_transferEncoding = 1;
            return;
        }

        if (this->_buffer.size() >= (pos + len) + 2 && this->_buffer.substr(pos + len, 2) == "\r\n")
            pos +=  len + 2;
        else
            return;
    }
}

// void HTTPRequest::isBodyCorrespondLength()
// {
//     size_t pos = this->_endHeader + 4;
// }

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