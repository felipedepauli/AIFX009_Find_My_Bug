#pragma once
#include <memory>
#include "Comm.h"

class Server {
private:
    std::unique_ptr<Comm> comm; // Comunicação com o cliente
public:
    Server();
    void start();
};
