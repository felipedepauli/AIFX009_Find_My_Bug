#include "server/Server.h"
#include "Comm.h" // Classe responsável pela comunicação

Server::Server() {
    comm = std::make_unique<Comm>(); // Instancia Comm
}

void Server::start() {
    comm->listen(); // Faz Comm "ouvir"
}

int main() {
    Server server; // Instancia o servidor
    server.start(); // Inicia o servidor
    return 0;
}
