#include <iostream>
#include <cstring>

#include "Resolver/Resolver.hpp"
#include "Net/TcpSocket.hpp"
#include "TLS/TlsSocket.hpp"

using namespace Wire;

int main() {
    SSL_library_init();
    SSL_load_error_strings();

    const std::string host = "google.com";
    const int port = 443;

    std::string ip = Resolver::resolveIPv4(host);
    std::cout << "IP: " << ip << "\n";

    TcpSocket tcp;
    if (!tcp.connectTo(ip.c_str(), port)) {
        std::cerr << "TCP connect failed\n";
        return 1;
    }

    TlsSocket tls;
    if (!tls.connect(tcp, host)) {
        std::cerr << "TLS connect failed\n";
        return 1;
    }

    const char* req =
        "GET / HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "User-Agent: Wire/0.1\r\n"
        "Connection: close\r\n\r\n";

    tls.send(req, strlen(req));

    char buf[4096];
    ssize_t n;
    while ((n = tls.recv(buf, sizeof(buf) - 1)) > 0) {
        buf[n] = 0;
        std::cout << buf;
    }

    return 0;
}
