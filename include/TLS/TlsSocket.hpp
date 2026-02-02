#pragma once

#include <openssl/ssl.h>
#include <string>

#include "Net/TcpSocket.hpp"

namespace Wire
{
    class TlsSocket
    {
    public:
        TlsSocket();
        ~TlsSocket();

        bool connect(TcpSocket &tcp, const std::string &host);
        ssize_t send(const void *data, size_t len);
        ssize_t recv(void *buf, size_t len);
        void close();

    private:
        SSL_CTX *ctx;
        SSL *ssl;
    };
}
