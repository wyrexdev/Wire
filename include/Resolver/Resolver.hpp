#pragma once

#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

namespace Wire
{
    class Resolver
    {
    public:
        static std::string resolveIPv4(const std::string &domain);
    };
} // namespace Wire
