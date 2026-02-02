#pragma once

#include "Core/Response.hpp"

namespace Wire
{
    namespace HTTP
    {
        class Parser
        {
        public:
            static Core::Response parse(const std::string& raw);
        };
    } // namespace HTTP
} // namespace Wire
