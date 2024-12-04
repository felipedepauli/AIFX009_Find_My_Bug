#include "server/processing/vision/VisionProcessor.h"

// Constructor: Initializes with a SimpleVision instance
VisionProcessor::VisionProcessor() : vision(std::make_unique<SimpleVision>()) {}

// Detect method: Delegates the frame to the VisionBase implementation
void VisionProcessor::detect(const cv::Mat& frame) {
    vision->detect(frame);
}

// Predict method: Delegates the frame to the VisionBase implementation
void VisionProcessor::predict(const cv::Mat& frame) {
    vision->predict(frame);
}

// Draw method: Delegates the frame to the VisionBase implementation
void VisionProcessor::draw(cv::Mat& frame) {
    vision->draw(frame);
}
