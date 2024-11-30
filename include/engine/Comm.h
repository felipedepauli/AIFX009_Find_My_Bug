#pragma once
#include <iostream>

class Comm {
public:
    Comm() {
        std::cout << "[Comm] Oiiii, estou aqui escutando por novas conexões!" << std::endl;
    }

    void listen() {
        std::cout << "[Comm] Escutando novas conexões..." << std::endl;
    }
};
