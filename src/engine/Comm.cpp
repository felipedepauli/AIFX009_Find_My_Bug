#include "Comm.h"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

Comm::Comm() {}

// Function to receive a single frame from the socket
cv::Mat Comm::receiveFrameFromSocket(boost::asio::ip::tcp::socket& socket) {
    try {
        // Receive frame size
        uint32_t frameSize;
        boost::asio::read(socket, boost::asio::buffer(&frameSize, sizeof(frameSize)));
        frameSize = ntohl(frameSize); // Converts from network byte order to host byte order

        if (frameSize == 1) { // Termination signal
            std::cout << "[Comm             ] Client sent termination signal. Closing connection." << std::endl;
            return cv::Mat(); // Return an empty frame to signal termination
        }

        // Read the frame data
        std::vector<uchar> frameData(frameSize);
        boost::asio::read(socket, boost::asio::buffer(frameData));
        std::cout << "[Comm             ] Received frame of size: " << frameData.size() << " bytes." << std::endl;

        // Decode the frame
        return cv::imdecode(frameData, cv::IMREAD_COLOR);
    } catch (std::exception& e) {
        std::cerr << "[Comm             ] Error receiving frame: " << e.what() << std::endl;
        return cv::Mat(); // Return an empty frame in case of error
    }
}

// Binds a socket to a Processing object and returns a callable task
std::function<void()> Comm::bind(boost::asio::ip::tcp::socket socket, std::shared_ptr<Processing> processing) {
    auto sharedSocket = std::make_shared<boost::asio::ip::tcp::socket>(std::move(socket));
    return [this, sharedSocket, processing]() mutable {
        try {
            while (processing->isRunning()) {
                auto frame = this->receiveFrameFromSocket(*sharedSocket);
                if (frame.empty()) {
                    std::cout << "[Comm             ] Connection closed." << std::endl;
                    processing->stop(); // Signal processing to stop
                    break; // Exit the loop
                }
                processing->run(frame);
            }
        } catch (std::exception& e) {
            std::cerr << "[Comm             ] Error in connection handler: " << e.what() << std::endl;
        }
    };
}

// Listens for incoming connections and returns the connected socket
boost::asio::ip::tcp::socket Comm::startListening(int port) {
    try {
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
        std::cout << "[Comm             ] Listening on port " << port << "..." << std::endl;

        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket); // Accepts a single connection
        std::cout << "[Comm             ] Connection established." << std::endl;

        return socket; // Return the connected socket
    } catch (std::exception& e) {
        std::cerr << "[Comm             ] Error: " << e.what() << std::endl;
        throw; // Re-throw the exception to signal failure
    }
}

// Sends a message to a specific host and port
void Comm::sendMessage(const std::string& message, const std::string& host, int port) {
    try {
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::string fullMessage = message + "\n";
        boost::asio::write(socket, boost::asio::buffer(fullMessage));
        std::cout << "[Comm             ] Message sent: " << message << std::endl;
    } catch (std::exception& e) {
        std::cerr << "[Comm             ] Error: " << e.what() << std::endl;
    }
}
