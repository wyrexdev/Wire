#pragma once

#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

#include "Utils/String.hpp"

namespace Wire
{
    class Resolver
    {
    public:
        static std::string resolveIPv4(const std::string &domain);
        static std::string resolveEndpoint(std::string input);
    };
} // namespace Wire
