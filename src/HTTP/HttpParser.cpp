#include "HTTP/HttpParser.hpp"

namespace Wire
{
    namespace HTTP
    {
        Core::Response Parser::parse(const std::string &raw)
        {
            Core::Response res;

            auto pos = raw.find("\r\n");
            if (pos == std::string::npos)
                throw std::runtime_error("Invalid HTTP response");

            std::string statusLine = raw.substr(0, pos);

            size_t p1 = statusLine.find(' ');
            size_t p2 = statusLine.find(' ', p1 + 1);

            if (p1 == std::string::npos)
                throw std::runtime_error("Invalid status line");

            res.httpVersion = statusLine.substr(0, p1);

            if (p2 == std::string::npos)
            {
                res.statusCode = std::stoi(statusLine.substr(p1 + 1));
                res.status.clear();
            }
            else
            {
                res.statusCode = std::stoi(
                    statusLine.substr(p1 + 1, p2 - p1 - 1));
                res.status = statusLine.substr(p2 + 1);
            }

            return res;
        }
    } // namespace HTTP
} // namespace Wire
