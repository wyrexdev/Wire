#pragma once

#include <string>

#include "Core/Request.hpp"

namespace Wire
{
    namespace HTTP
    {
        class Builder
        {
        public:
            static std::string build(const Core::Request& req);
        };
    } // namespace HTTP
} // namespace Wire
