#ifndef VISIONPROCESSOR_H
#define VISIONPROCESSOR_H

#include "VisionBase.h"
#include "server/processing/vision/implYolo.h"
#include "server/processing/vision/TrackingProcessor.h"
#include "ByteTrack/BYTETracker.h"
#include <memory>
#include <iostream>

// VisionProcessor serves as a wrapper for the selected VisionBase implementation.
class VisionProcessor {
private:
    std::unique_ptr<SimpleVision> vision;
    std::unique_ptr<TrackingProcessor> tracking;

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
