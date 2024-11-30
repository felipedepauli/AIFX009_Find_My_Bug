#include "server/Server.h"
#include "Comm.h"
#include <iostream>

int main() {
    try {
        Comm comm;
        comm.startListening(8080);
    } catch (std::exception& e) {
        std::cerr << "[Server] Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
