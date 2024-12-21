#ifndef SERVER_HPP
#define SERVER_HPP

#include <opencv2/opencv.hpp>
#include <memory>
#include <functional>
#include "processing/vision/VisionProcessor.hpp"
#include "connectors/Kafka.hpp"

// Forward declaration of classes
class Comm;

// The Server class encapsulates the logic for handling frames
class Server {
private:
    bool running;
    std::unique_ptr<VisionProcessor> vision;
    std::unique_ptr<Kafka> producer;

public:
    Server();
    ~Server() {}

    void stop();
    bool isRunning() const;
    void run(const cv::Mat& frame);
};

#endif // SERVER_HPP
