#include "HTTP/HttpBuilder.hpp"

namespace Wire
{
    namespace HTTP
    {
        std::string Builder::build(const Core::Request& req) {
            std::string headers;
            std::string body = req.body;

            for(auto h : req.headers) {
                std::string header = h.second.key + ": " + h.second.val;
                headers += (header + "\n");
            }

            return headers + "\n" + body;
        }
    } // namespace HTTP
} // namespace Wire
