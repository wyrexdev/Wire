#include "Client/WireClient.hpp"

int main() {
    Wire::WireClient *client = new Wire::WireClient();

    std::cout << client->get("https://google.com").statusCode << std::endl;

    return 0;
}
