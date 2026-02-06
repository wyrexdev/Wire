#include "Client/WireClient.hpp"

int main() {
    Wire::WireClient *client = new Wire::WireClient();

    // client->get("https://netflix.com").body;
    std::cout << client->get("https://netflix.com").body << std::endl;

    return 0;
}
