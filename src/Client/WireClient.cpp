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

    // In the here we need depth for too much redirect
    Core::Response WireClient::get(std::string addr, std::string s, std::string h, int depth = 0)
    {
        int port = 443;
        std::string path = "/";
        std::string scheme = "https";

        auto schemeSplit = Utils::String::split(addr, "://");
        if (schemeSplit.size() > 1)
        {
            scheme = schemeSplit[0];
            addr = schemeSplit[1];

            port = (scheme == "https") ? 443 : 80;
        }
        else
        {
            addr = h + "/" + addr;
            port = 443;
        }

        s = scheme;

        auto pathSplit = Utils::String::split(addr, "/");

        size_t slashPos = addr.find('/');
        if (slashPos != std::string::npos)
        {
            path = addr.substr(slashPos);
        }

        std::string host = pathSplit[0];
        std::string referer = scheme + "://" + host;

        h = host;

        std::string ip = Resolver::resolveIPv4(host);

        TcpSocket tcp;
        if (!tcp.connectTo(ip.c_str(), port))
        {
            std::cerr << "TCP connect failed\n";
        }

        TlsSocket tls;
        if (!tls.connect(tcp, host))
        {
            std::cerr << "TLS connect failed\n";
        }

        std::string req =
            ("GET " + path + " HTTP/1.1\r\n") +
            ("Host: " + host + "\r\n") +
            ("Accept-Language: " + Utils::System::getLanguage() + "\r\n") +
            "User-Agent: Void-Wire/0.1\r\n"
            "Connection: close\r\n\r\n";

        tls.send(req.data(), req.size());

        std::string raw;
        char buf[4096];

        while (true)
        {
            ssize_t n = tls.recv(buf, sizeof(buf));

            if (n > 0)
            {
                raw.append(buf, n);
                continue;
            }

            if (n == 0)
            {
                break;
            }

            int err = tls.lastError(n);
            if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE)
            {
                continue;
            }

            break;
        }

        Core::Response res = HTTP::Parser::parse(raw);

        if (depth >= 10)
        {
            if (!(res.statusCode.has_value()))
            {
                Core::Response tmr;
                std::string content = FS::FileSystem::readFile("./system-pages/redirects/too-much-redirect.html");
                tmr.body = content;

                return tmr;
            }
        }

        depth++;

        auto redirect = res.headers.find("location");
        if (redirect != res.headers.end())
        {
            std::cout << "Redirected to: " << redirect->second.val << std::endl;
            return get(redirect->second.val, scheme, host, depth);
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
        }

        TlsSocket tls;
        if (!tls.connect(tcp, addr))
        {
            std::cerr << "TLS connect failed\n";
        }

        const char *req =
            "POST / HTTP/1.1\r\n"
            "Host: google.com\r\n"
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
