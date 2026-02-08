#include "HTTP/HttpParser.hpp"

namespace Wire
{
    namespace HTTP
    {
        Core::Response Parser::parse(const std::string &raw)
        {
            Core::Response res;

            size_t pos = raw.find("\r\n");
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
                res.statusCode = std::stoi(statusLine.substr(p1 + 1, p2 - p1 - 1));
                res.status = statusLine.substr(p2 + 1);
            }

            size_t headerStart = pos + 2;
            size_t headerEnd = raw.find("\r\n\r\n", headerStart);
            if (headerEnd == std::string::npos)
                throw std::runtime_error("Invalid headers");

            std::string headersBlock = raw.substr(headerStart, headerEnd - headerStart);
            auto lines = Utils::String::split(headersBlock, "\r\n");

            for (const auto &line : lines)
            {
                // std::cout << "Line: " << line << std::endl;

                auto colon = line.find(':');
                if (colon == std::string::npos)
                    continue;

                std::string key =
                    Utils::String::toLowerCase(Utils::String::trim(line.substr(0, colon)));

                std::string value =
                    Utils::String::trim(line.substr(colon + 1));

                res.headers[key] = {key, value};
            }

            if (res.statusCode.has_value() && (res.statusCode.value() / 100 == 1 ||
                res.statusCode.value() == 204 ||
                res.statusCode.value() == 304))
            {
                return res;
            }

            size_t bodyStart = headerEnd + 4;
            std::string rawBody = raw.substr(bodyStart);

            auto te = res.headers.find("transfer-encoding");
            if (te != res.headers.end() &&
                Utils::String::toLowerCase(te->second.val) == "chunked")
            {
                std::string out;
                size_t p = 0;

                while (true)
                {
                    size_t lineEnd = rawBody.find("\r\n", p);
                    if (lineEnd == std::string::npos)
                        break;

                    std::string sizeStr = rawBody.substr(p, lineEnd - p);
                    size_t chunkSize = std::stoul(sizeStr, nullptr, 16);

                    if (chunkSize == 0)
                        break;

                    p = lineEnd + 2;
                    out.append(rawBody.substr(p, chunkSize));
                    p += chunkSize + 2;
                }

                res.body = out;
                return res;
            }

            auto cl = res.headers.find("content-length");
            if (cl != res.headers.end())
            {
                size_t len = std::stoul(cl->second.val);
                res.body = rawBody.substr(0, len);
                return res;
            }

            auto ce = res.headers.find("content-encoding");
            if(ce != res.headers.end()) {
                std::string encoding = ce->second.val;

                Core::Codec::Type type = Core::Codec::Type::fromHeader(encoding);
                auto decoder = Core::Codec::Factory::create(type);
            }

            res.body = rawBody;
            return res;
        }
    } // namespace HTTP
} // namespace Wire
