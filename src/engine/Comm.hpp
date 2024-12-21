#ifndef COMM_HPP
#define COMM_HPP

#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>
#include <functional>
#include <vector>
#include "server/Server.hpp"

class Comm {
private:
    boost::asio::io_context io_context;

    // Helper to receive a frame from a socket
    cv::Mat receiveFrameFromSocket(boost::asio::ip::tcp::socket& socket);

public:
    // Constructor
    Comm();

    // Handles a single client connection
    void handleConnection(boost::asio::ip::tcp::socket socket, std::function<void(const cv::Mat&)> processFrame);

    // Binds a socket to a processing object and returns a callable task
    std::function<void()> bind(boost::asio::ip::tcp::socket socket, std::shared_ptr<Processing> processing);

    // Listens for incoming connections and returns the connected socket
    boost::asio::ip::tcp::socket startListening(int port);

    // Sends a message to a specific host and port
    void sendMessage(const std::string& message, const std::string& host, int port);
};

#endif // COMM_H
