#pragma once

#include <string>

namespace Wire
{
    namespace HTTP
    {
        struct Header
        {
            std::string key;
            std::string val;
        };
    } // namespace Core
} // namespace Wire