#ifndef VISIONBASE_H
#define VISIONBASE_H

#include <opencv2/opencv.hpp>

class VisionBase {
public:
    virtual ~VisionBase() = default;

    // Method to detect objects in a frame
    virtual void detect(const cv::Mat& frame) = 0;

    // Placeholder methods for further implementation
    virtual void predict(const cv::Mat& frame) = 0;
    virtual void draw(cv::Mat& frame) = 0;
};

#endif // VISIONBASE_H
