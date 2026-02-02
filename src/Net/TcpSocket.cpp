#include "Net/TcpSocket.hpp"

namespace Wire
{
    bool TcpSocket::connect(char *domain, char *port)
    {
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        if (getaddrinfo(domain, port, &hints, &res) != 0)
        {
            std::cerr << "DNS resolve failed\n";
            return 1;
        }

        sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sock < 0)
        {
            perror("socket");
            return 1;
        }

        if (connect(sock, res->ai_addr, res->ai_addrlen) < 0)
        {
            perror("connect");
            close(sock);
            return 1;
        }

        freeaddrinfo(res);
    }

    void TcpSocket::close()
    {
    }
} // namespace Wire
