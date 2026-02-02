#include "Net/TcpSocket.hpp"

namespace Wire
{
    TcpSocket::TcpSocket() : sock(-1) {}
    TcpSocket::~TcpSocket() { close(); }

    bool TcpSocket::connectTo(const char *ip, int port)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
            return false;

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, ip, &addr.sin_addr);

        if (connect(sock, (sockaddr *)&addr, sizeof(addr)) < 0)
        {
            close();
            return false;
        }
        return true;
    }

    ssize_t TcpSocket::send(const void *data, size_t len)
    {
        return ::send(sock, data, len, 0);
    }

    ssize_t TcpSocket::recv(void *buf, size_t len)
    {
        return ::recv(sock, buf, len, 0);
    }

    int TcpSocket::fd() const { return sock; }

    void TcpSocket::close()
    {
        if (sock != -1)
        {
            ::close(sock);
            sock = -1;
        }
    }
} // namespace Wire
