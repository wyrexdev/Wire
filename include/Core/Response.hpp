#pragma once

#include <string>
#include <unordered_map>
#include <optional>

#include "HTTP/Header/Header.hpp"

namespace Wire
{
    namespace Core
    {
        struct Response
        {
            std::string httpVersion;
            
            std::optional<int> statusCode;
            std::string status;

            std::unordered_map<std::string, HTTP::Header> headers;

            std::string body;
        };
        
    } // namespace Core
} // namespace Wire