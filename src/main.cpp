#include "Client/WireClient.hpp"

int main() {
    Wire::WireClient *client = new Wire::WireClient();

    // client->get("https://netflix.com").body;
    std::cout << client->get("https://httpbin.org/redirect/1", "https", "httpbin.org", 0).body << std::endl;

    // std::cout << Wire::Resolver::resolveEndpoint("https://httpbin.org/redirect/10") << std::endl;
    
    return 0;
}
