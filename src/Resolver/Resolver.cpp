#include "Resolver/Resolver.hpp"

namespace Wire
{
    std::string Resolver::resolveIPv4(const std::string &domain)
    {
        addrinfo hints{}, *res;

        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        if (getaddrinfo(domain.c_str(), nullptr, &hints, &res) != 0)
        {
            throw std::runtime_error("DNS resolve failed");
        }

        char ip[INET_ADDRSTRLEN];
        auto *addr = (sockaddr_in *)res->ai_addr;
        inet_ntop(AF_INET, &addr->sin_addr, ip, sizeof(ip));

        freeaddrinfo(res);
        return ip;
    }

    std::string Resolver::resolveEndpoint(std::string input)
    {
        auto schemeSplit = Utils::String::split(input, "://");
        std::string hostPart;

        if (schemeSplit.size() >= 2)
            hostPart = schemeSplit[1];
        else
            hostPart = schemeSplit[0];

        auto pathSplit = Utils::String::split(hostPart, "/");
        if (!pathSplit.empty())
            return pathSplit[0];

        return hostPart;
    }
} // namespace Wire
