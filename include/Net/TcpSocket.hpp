#pragma once

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

namespace Wire
{
    class TcpSocket
    {
    public:
        bool connect(char* domain, char* port);
        ssize_t send(const void *data, size_t len);
        ssize_t recv(void *buf, size_t len);
        void close();

    private:
        int sock;

        addrinfo hints{};
        addrinfo *res;
    };
} // namespace Wire
