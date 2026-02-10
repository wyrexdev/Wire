#include "HTTP/Chunked.hpp"

#include <stdexcept>

namespace Wire::HTTP
{
    std::string decodeChunked(const std::string &in)
    {
        std::string out;
        size_t p = 0;

        while (true)
        {
            size_t lineEnd = in.find("\r\n", p);
            if (lineEnd == std::string::npos)
                break;

            std::string sizeLine = in.substr(p, lineEnd - p);

            size_t semi = sizeLine.find(';');
            if (semi != std::string::npos)
                sizeLine = sizeLine.substr(0, semi);

            size_t chunkSize = std::stoul(sizeLine, nullptr, 16);
            p = lineEnd + 2;

            if (chunkSize == 0)
                break;

            if (p + chunkSize > in.size())
                throw std::runtime_error("Chunk overflow");

            out.append(in, p, chunkSize);
            p += chunkSize;

            if (in.compare(p, 2, "\r\n") != 0)
                throw std::runtime_error("Invalid chunk CRLF");

            p += 2;
        }

        return out;
    }
}
