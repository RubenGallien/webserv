#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

struct HTTPRequest 
{

    HTTPRequest();
    HTTPRequest(const HTTPRequest& src);
    HTTPRequest& operator=(const HTTPRequest& other);

    bool                                complete;   
    std::string                         start_line;
    std::map<std::string, std::string>  headers;
    std::string                         body;

    ~HTTPRequest();

};

#endif