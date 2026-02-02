int main()
{
    const char* domain = "www.google.com";
    const char* port   = "443";

    /* ---------- DNS RESOLVE ---------- */
    addrinfo hints{};
    addrinfo* res;

    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(domain, port, &hints, &res) != 0)
    {
        std::cerr << "DNS resolve failed\n";
        return 1;
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
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

    /* ---------- OPENSSL INIT ---------- */
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx)
    {
        ERR_print_errors_fp(stderr);
        return 1;
    }

    /* Sertifika doğrulama AÇIK */
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, nullptr);
    SSL_CTX_set_default_verify_paths(ctx);

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    SSL_set_tlsext_host_name(ssl, domain); // SNI (ÇOK ÖNEMLİ)

    if (SSL_connect(ssl) <= 0)
    {
        ERR_print_errors_fp(stderr);
        return 1;
    }

    std::cout << "TLS connected using "
              << SSL_get_cipher(ssl) << "\n";

    /* ---------- HTTPS REQUEST ---------- */
    std::string req =
        "GET / HTTP/1.1\r\n"
        "Host: www.google.com\r\n"
        "Connection: close\r\n\r\n";

    SSL_write(ssl, req.c_str(), req.size());

    char buf[4096];
    int bytes;

    while ((bytes = SSL_read(ssl, buf, sizeof(buf) - 1)) > 0)
    {
        buf[bytes] = 0;
        std::cout << buf;
    }

    /* ---------- CLEANUP ---------- */
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sock);

    return 0;
}
