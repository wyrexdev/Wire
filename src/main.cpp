#include "Client/WireClient.hpp"

int main() {
    Wire::WireClient *client = new Wire::WireClient();

    std::cout << client->get("https://www.google.com/webhp").body << std::endl;

    return 0;
}
