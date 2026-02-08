#include "Client/WireClient.hpp"

int main() {
    Wire::WireClient *client = new Wire::WireClient();

    // client->get("https://netflix.com").body;
    // std::cout << client->get("google.com", "https", "google.com", 0).body << std::endl;

    client->get("google.com", "https", "google.com", 0);

    // std::cout << Wire::Resolver::resolveEndpoint("https://httpbin.org/redirect/10") << std::endl;
    
    return 0;
}
