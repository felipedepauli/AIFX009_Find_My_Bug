#ifndef VISIONPROCESSOR_H
#define VISIONPROCESSOR_H

#include "VisionBase.h"
#include "server/processing/vision/implYolo.h"
#include <memory>

// VisionProcessor serves as a wrapper for the selected VisionBase implementation.
class VisionProcessor {
private:
    std::unique_ptr<SimpleVision> vision;

public:
    // Constructor: Initializes with a SimpleVision instance
    VisionProcessor();

    // Delegate methods to the VisionBase implementation
    void detect(const cv::Mat& frame);
    void predict(const cv::Mat& frame);
    void draw(cv::Mat& frame);
};

#endif // VISIONPROCESSOR_H
