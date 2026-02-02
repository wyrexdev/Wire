#pragma once

#include <string>

#include "Core/Response.hpp"

namespace Wire
{
    class WireClient
    {
    public:
        WireClient();
        ~WireClient();

        Core::Response get(std::string addr);
        Core::Response post(std::string addr);
    };
} // namespace Wire
