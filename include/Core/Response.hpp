#pragma once

#include <string>
#include <unordered_map>

#include "HTTP/Header/Header.hpp"

namespace Wire
{
    namespace Core
    {
        struct Response
        {
            std::string body;
            
            std::unordered_map<std::string, HTTP::Header> headers;
            
            int statusCode;
        };
        
    } // namespace Core
} // namespace Wire