#ifndef HTTPREQUESTPARSER
#define HTTPREQUESTPARSER

#include "HTTPRequest.hpp"
#include <locale>

class HTTPRequestParser
{

    private:
        HTTPRequestParser();
        HTTPRequestParser(const HTTPRequestParser& src);
        HTTPRequestParser& operator=(const HTTPRequestParser& other);
        ~HTTPRequestParser();
    public:
        static void fillRequest(HTTPRequest& request, std::string& buffer);
        static void checkIfComplete(HTTPRequest& request, std::string& buffer);
        static int hasCompleteRequest(std::string& buffer);

};


#endif