#pragma once

#include <iostream>

#include "Core/Response.hpp"
#include "Utils/String.hpp"

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
