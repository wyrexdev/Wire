#include "Client/WireClient.hpp"

namespace Wire
{
    WireClient::WireClient()
    {
        SSL_library_init();
        SSL_load_error_strings();
    }

    WireClient::~WireClient()
    {
    }

    Core::Response WireClient::get(std::string addr)
    {
        int port = 443;

        if (Utils::String::split(addr, "://").size() > 0)
        {
            std::cout << Utils::String::split(addr, "://")[0] << std::endl;
            if (Utils::String::split(addr, "://")[0] == "https")
            {
                port = 443;
            }
            else
            {
                port = 80;
            }

            addr = Utils::String::split(addr, "://")[1];
        }

        Core::Response res;

        std::string ip = Resolver::resolveIPv4(addr);
        std::cout << "IP: " << ip << "\n";

        TcpSocket tcp;
        if (!tcp.connectTo(ip.c_str(), port))
        {
            std::cerr << "TCP connect failed\n";
            // return 1;
        }

        TlsSocket tls;
        if (!tls.connect(tcp, addr))
        {
            std::cerr << "TLS connect failed\n";
            // return 1;
        }

        const char *req =
            "GET / HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "User-Agent: Void-Wire/0.1\r\n"
            "Connection: close\r\n\r\n";

        tls.send(req, strlen(req));

        char buf[4096];
        ssize_t n;
        while ((n = tls.recv(buf, sizeof(buf) - 1)) > 0)
        {
            buf[n] = 0;
            res.body += buf;
        }

        return res;
    }

    Core::Response WireClient::post(std::string addr)
    {
        Core::Response res;

        std::string ip = Resolver::resolveIPv4(addr);
        std::cout << "IP: " << ip << "\n";

        const int port = 443;

        TcpSocket tcp;
        if (!tcp.connectTo(ip.c_str(), port))
        {
            std::cerr << "TCP connect failed\n";
            // return 1;
        }

        TlsSocket tls;
        if (!tls.connect(tcp, addr))
        {
            std::cerr << "TLS connect failed\n";
            // return 1;
        }

        const char *req =
            "POST / HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "User-Agent: Void-Wire/0.1\r\n"
            "Connection: close\r\n\r\n";

        tls.send(req, strlen(req));

        char buf[4096];
        ssize_t n;
        while ((n = tls.recv(buf, sizeof(buf) - 1)) > 0)
        {
            buf[n] = 0;
            res.body += buf;
        }

        return res;
    }
} // namespace Wire
