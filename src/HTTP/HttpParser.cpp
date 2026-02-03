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

            size_t headerStart = pos + 2;
            size_t headerEnd = raw.find("\r\n\r\n", headerStart);

            if (headerEnd == std::string::npos)
                throw std::runtime_error("Invalid headers");

            std::string headersBlock =
                raw.substr(headerStart, headerEnd - headerStart);

            auto lines = Utils::String::split(headersBlock, "\r\n");

            for (const auto &line : lines)
            {
                auto colon = line.find(':');
                if (colon == std::string::npos)
                    continue;

                std::string key = Utils::String::toLowerCase(Utils::String::trim(line.substr(0, colon)));
                std::string value = Utils::String::trim(line.substr(colon + 1));

                res.headers[key] = {key, value};
            }

            bool hasBody = true;

            if (res.statusCode / 100 == 1 ||
                res.statusCode == 204 ||
                res.statusCode == 304)
            {
                hasBody = false;
            }

            auto cl = res.headers.find("content-length");
            if (cl != res.headers.end())
            {
                int len = std::stoi(cl->second.val);
                size_t bodyStart = headerEnd + 4;

                res.body = raw.substr(bodyStart, len);
            }

            return res;
        }
    } // namespace HTTP
} // namespace Wire
