#ifndef COMM_H
#define COMM_H

#include <boost/asio.hpp>
#include <string>

class Comm {
public:
    Comm(); // Construtor

    // Servidor
    void startListening(int port);

    // Cliente
    void sendMessage(const std::string& message, const std::string& host, int port);

private:
    boost::asio::io_context io_context;
};

#endif // COMM_H
