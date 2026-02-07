#include "Client/WireClient.hpp"

int main() {
    Wire::WireClient *client = new Wire::WireClient();

    // client->get("https://netflix.com").body;
    std::cout << client->get("https://httpbin.org/redirect/10", "https", "httpbin.org", 0).body << std::endl;

    return 0;
}
