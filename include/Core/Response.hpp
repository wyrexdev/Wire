#pragma once

#include <string>

namespace Wire
{
    namespace Core
    {
        struct Response
        {
            std::string body;
            
            int statusCode;
        };
        
    } // namespace Core
} // namespace Wire