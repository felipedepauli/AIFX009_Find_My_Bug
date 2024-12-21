#ifndef VISIONPROCESSOR_H
#define VISIONPROCESSOR_H

#include "VisionBase.hpp"
#include "detectors/implYolo.hpp"
#include "TrackingProcessor.hpp"
#include "ByteTrack/BYTETracker.h"
#include <memory>
#include <iostream>
#include <string>

// VisionProcessor serves as a wrapper for the selected VisionBase implementation.
class VisionProcessor {
private:
    std::unique_ptr<SimpleVision> vision;
    std::unique_ptr<TrackingProcessor> tracking;
    int frameCounter;

public:
    // Constructor: Initializes with a SimpleVision instance
    VisionProcessor();

    // Delegate methods to the VisionBase implementation
    void detect(const cv::Mat& frame);
    void predict(const cv::Mat& frame);
    void draw(cv::Mat& frame);
    void track();
};

#endif // VISIONPROCESSOR_H
