#include "TLS/TlsSocket.hpp"

namespace Wire
{

    TlsSocket::TlsSocket() : ctx(nullptr), ssl(nullptr) {}

    TlsSocket::~TlsSocket()
    {
        close();
    }

    bool TlsSocket::connect(TcpSocket &tcp, const std::string &host)
    {
        ctx = SSL_CTX_new(TLS_client_method());
        if (!ctx)
            return false;

        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, nullptr);
        SSL_CTX_set_default_verify_paths(ctx);

        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, tcp.fd());

        SSL_set_tlsext_host_name(ssl, host.c_str());

        const unsigned char alpn[] = {
            8, 'h', 't', 't', 'p', '/', '1', '.', '1'};

        SSL_set_alpn_protos(ssl, alpn, sizeof(alpn));

        if (SSL_connect(ssl) <= 0)
        {
            ERR_print_errors_fp(stderr);
            return false;
        }
        
        return true;
    }

    ssize_t TlsSocket::send(const void *data, size_t len)
    {
        return SSL_write(ssl, data, len);
    }

    ssize_t TlsSocket::recv(void *buf, size_t len)
    {
        return SSL_read(ssl, buf, len);
    }

    void TlsSocket::close()
    {
        if (ssl)
        {
            SSL_shutdown(ssl);
            SSL_free(ssl);
            ssl = nullptr;
        }
        if (ctx)
        {
            SSL_CTX_free(ctx);
            ctx = nullptr;
        }
    }

    int TlsSocket::lastError(int ret)
    {
        return SSL_get_error(ssl, ret);
    }

} // namespace Wire