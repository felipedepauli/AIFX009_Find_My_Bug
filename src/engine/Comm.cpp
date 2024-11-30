#include "Comm.h"
#include <iostream>

Comm::Comm() {}

void Comm::startListening(int port) {
    try {
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
        std::cout << "[Comm] Listening on port " << port << "..." << std::endl;

        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        std::cout << "[Comm] Connection established." << std::endl;

        boost::asio::streambuf buffer;
        boost::asio::read_until(socket, buffer, "\n");
        std::string message = boost::asio::buffer_cast<const char*>(buffer.data());
        std::cout << "[Comm] Received message: " << message << std::endl;
    } catch (std::exception& e) {
        std::cerr << "[Comm] Error: " << e.what() << std::endl;
    }
}

void Comm::sendMessage(const std::string& message, const std::string& host, int port) {
    try {
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::string fullMessage = message + "\n";
        boost::asio::write(socket, boost::asio::buffer(fullMessage));
        std::cout << "[Comm] Message sent: " << message << std::endl;
    } catch (std::exception& e) {
        std::cerr << "[Comm] Error: " << e.what() << std::endl;
    }
}
