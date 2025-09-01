#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest()
{
    this->complete = false;
    this->complete_body = false;
    return;
}

HTTPRequest::HTTPRequest(const HTTPRequest& src)
{
    *this = src;
    return;
}

HTTPRequest& HTTPRequest::operator=(const HTTPRequest& other)
{
    this->complete = other.complete;
    this->start_line = other.complete;
    this->headers = other.headers;
    this->body = other.body;
    return *this;
}

HTTPRequest::~HTTPRequest()
{
    return;
}