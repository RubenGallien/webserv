#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest()
{
    return;
}

HTTPRequest::HTTPRequest(std::string req)
{
    std::cout << req << std::endl;
 
    std::cout << "Create an HTTP Request" << std::endl;
}


// HTTPRequest::HTTPRequest(std::string req)
// {
//     std::string start_line(req.substr(0, req.find("\n")));
//     std::istringstream f(start_line);

//     std::string method, path, version;
//     f >> method >> path >> version;
//     this->_method = method;
//     this->_path = path;
//     this->_version = version;
 
//     std::cout << "Create an HTTP Request" << std::endl;
// }


HTTPRequest::~HTTPRequest()
{
    
}