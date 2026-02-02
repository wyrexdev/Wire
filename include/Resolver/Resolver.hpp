#pragma once

#include <string>

namespace Wire
{
    class Resolver
    {
    public:
        static std::string resolveIPv4(const std::string &domain);
    };
} // namespace Wire
