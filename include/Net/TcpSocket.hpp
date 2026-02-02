#pragma once

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "Resolver/Resolver.hpp"

namespace Wire
{
    class TcpSocket
    {
    public:
        TcpSocket();
        ~TcpSocket();

        bool connectTo(const char *ip, int port);
        ssize_t send(const void *data, size_t len);
        ssize_t recv(void *buf, size_t len);

        int fd() const;
        void close();

    private:
        int sock;
    };
} // namespace Wire
