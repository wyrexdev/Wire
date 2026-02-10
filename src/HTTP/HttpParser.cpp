#include "HTTP/HttpParser.hpp"
#include "HTTP/Chunked.hpp"

#include "Core/Codec/Gzip/Gzip.hpp"

#include <algorithm>

static std::string toLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

namespace Wire::HTTP
{
    Core::Response Parser::parse(const std::string& raw)
    {
        Core::Response res;

        size_t pos = raw.find("\r\n");
        if (pos == std::string::npos)
            throw std::runtime_error("Invalid HTTP response");

        std::string statusLine = raw.substr(0, pos);
        size_t p1 = statusLine.find(' ');
        size_t p2 = statusLine.find(' ', p1 + 1);

        res.httpVersion = statusLine.substr(0, p1);
        res.statusCode = std::stoi(statusLine.substr(p1 + 1, p2 - p1 - 1));
        res.status = statusLine.substr(p2 + 1);

        size_t headerEnd = raw.find("\r\n\r\n", pos);
        if (headerEnd == std::string::npos)
            throw std::runtime_error("Invalid headers");

        size_t headerStart = pos + 2;
        std::string headerBlock = raw.substr(headerStart, headerEnd - headerStart);

        size_t off = 0;
        while (true)
        {
            size_t e = headerBlock.find("\r\n", off);
            std::string line = headerBlock.substr(off, e - off);
            off = (e == std::string::npos) ? e : e + 2;

            auto c = line.find(':');
            if (c != std::string::npos)
            {
                std::string k = toLower(line.substr(0, c));
                std::string v = line.substr(c + 1);
                v.erase(0, v.find_first_not_of(" "));
                res.headers[k] = {k, v};
            }

            if (e == std::string::npos)
                break;
        }

        std::string body = raw.substr(headerEnd + 4);

        auto te = res.headers.find("transfer-encoding");
        if (te != res.headers.end() && toLower(te->second.val) == "chunked")
            body = decodeChunked(body);

        auto ce = res.headers.find("content-encoding");
        if (ce != res.headers.end() && toLower(ce->second.val) == "gzip")
        {
            Core::Codec::Gzip gzip;
            std::vector<uint8_t> out;
            gzip.decode((uint8_t*)body.data(), body.size(), out);
            body.assign(out.begin(), out.end());
        }

        res.body = std::move(body);
        return res;
    }
}
