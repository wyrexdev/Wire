#pragma once

#include <iostream>
#include <cstring>

#include "Resolver/Resolver.hpp"
#include "Net/TcpSocket.hpp"
#include "TLS/TlsSocket.hpp"
#include "Core/Response.hpp"
#include "Utils/String.hpp"
#include "Utils/System.hpp"
#include "Utils/FS.hpp"
#include "HTTP/HttpParser.hpp"

namespace Wire
{
    class WireClient
    {
    public:
        WireClient();
        ~WireClient();

        Core::Response get(std::string addr, std::string scheme, std::string host, int depth);
        Core::Response post(std::string addr);
    };
} // namespace Wire
