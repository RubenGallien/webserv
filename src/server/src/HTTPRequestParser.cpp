#include "HTTPRequestParser.hpp"

HTTPRequestParser::HTTPRequestParser()
{
    return;
}

HTTPRequestParser::HTTPRequestParser(const HTTPRequestParser & src)
{
    *this = src;
    return;
}

HTTPRequestParser& HTTPRequestParser::operator=(const HTTPRequestParser& other)
{
    (void)other;
    return *this;
}

void addHeaderField(HTTPRequest& request, std::string line)
{
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    size_t colon_pos = line.find(":");
    std::string lvalue(line.substr(0, colon_pos));
    std::string rvalue(line.substr(colon_pos));
    std::locale loc;
    for (std::string::size_type i=0; i<lvalue.length(); ++i)
        std::tolower(lvalue[i],loc);
    request.headers[lvalue] = rvalue;
}

void addStartLine(HTTPRequest& request, std::string line)
{
    std::istringstream ss(line);
    std::string method;
    std::string uri;
    std::string protocol;
    ss >> method >> uri >> protocol;
    request.start_line = method + uri + protocol;
}

int isChunkedComplete(std::string& buffer)
{
    size_t pos = 0;

    while (true)
    {
        size_t endline = buffer.find("\r\n", pos);

        if (endline == std::string::npos)
            return 0;

        std::string lenStr = buffer.substr(pos, endline);

        int len;
        std::istringstream(lenStr) >> len;

        pos += endline + 2;
        if (len == 0)
        {
            if (buffer.size() >= pos + 2 && buffer.substr(pos, 2) == "\r\n")
                return 1;
        }

        if (buffer.size() >= (pos + len) + 2 && buffer.substr(pos + len, 2) == "\r\n")
            pos +=  len + 2;
        else
            return 0;
    }
    return 0;
}

int isBodyCorrespondLength(std::string& length, std::string& buffer)
{
    std::istringstream ss(length);
    size_t size;
    ss >> size;
    if (size == buffer.size())
        return 1;
    return 0;
}

void HTTPRequestParser::checkIfComplete(HTTPRequest& request, std::string& buffer)
{
    std::map<std::string,std::string>::iterator it;
    it = request.headers.find("content-length");
    if (it != request.headers.end())
    {
        if (isBodyCorrespondLength(it->second, buffer))
            request.complete = true;
        return;
    }
    it = request.headers.find("transfer-encoding");
    if (it != request.headers.end() && it->second == "chunked")
    {
        if (isChunkedComplete(buffer))
            request.complete = true;
        return;
    }
    request.complete = true;
}

void HTTPRequestParser::fillRequest(HTTPRequest& request, std::string& buffer)
{
    std::cout << "Buffer dans fillRequest = " << buffer << "$" << std::endl;
    size_t findLine = buffer.find("\r\n");
    while (!request.complete_body && findLine != std::string::npos)
    {
        if (findLine == 0)
        {
            request.complete_body = true;
            buffer.erase(0, 2);
            std::cout << "FIN DE HEADER DETECTE" << std::endl;
            break;
        }
        size_t colon_pos = buffer.find(":");
        std::string toAdd = buffer.substr(0, findLine);
        if (colon_pos == std::string::npos)
            addStartLine(request, toAdd);
        else
            addHeaderField(request, toAdd);
        buffer.erase(0, findLine+2);
        findLine = buffer.find("\r\n");
    }
    if (request.complete_body && !request.complete)
        HTTPRequestParser::checkIfComplete(request, buffer);
    return;
}

HTTPRequestParser::~HTTPRequestParser()
{
    return;
}