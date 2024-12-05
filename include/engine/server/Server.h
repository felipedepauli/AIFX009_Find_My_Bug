#ifndef SERVER_H
#define SERVER_H

#include <opencv2/opencv.hpp>
#include <memory>
#include <functional>
#include "server/processing/vision/VisionProcessor.h"

// Forward declaration of classes
class Comm;

// The Processing class encapsulates the logic for handling frames
class Processing {
private:
    bool running;
    VisionProcessor vision;

public:
    Processing() : running(true) {}
    ~Processing() {
        cv::destroyAllWindows();
    }

    void stop() {
        running = false;
    }

    bool isRunning() const {
        return running;
    }

    void run(const cv::Mat& frame) {
        if (!running) return; // Stop processing if the flag is false

        // Vision-based detection
        vision.detect(frame);
        vision.track();

        // Waits 30ms or exits if 'q' is pressed
        if (cv::waitKey(30) == 'q') {
            std::cout << "[Server] Playback interrupted by user." << std::endl;
            running = false;
        }
    }
};

#endif // SERVER_H
