#include "comm/Server.h"
#include "comm/Client.h"

int main() {
    std::cout << "Starting AIFX009 System..." << std::endl;

    Server server;
    Client client;

    server.start();
    client.connect();

    return 0;
}
