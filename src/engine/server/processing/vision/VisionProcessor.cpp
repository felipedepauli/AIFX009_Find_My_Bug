#include "server/processing/vision/VisionProcessor.h"

// Constructor: Initializes with a SimpleVision and TrackingProcessor instance
VisionProcessor::VisionProcessor()
    : vision(std::make_unique<SimpleVision>()),
      tracking(std::make_unique<TrackingProcessor>()) {}

// Detect method: Delegates the frame to the VisionBase implementation
void VisionProcessor::detect(const cv::Mat& frame) {
    // Performs detection with the original frame (const)
    Detections detections = vision->detect(frame);

    // Creates a copy to modify
    cv::Mat modifiableFrame = frame.clone();

    // Updates tracking and draws the bounding boxes on the copy
    tracking->updateDetections(detections, modifiableFrame);

    // Displays the modified frame (optional)
    try {
        cv::imshow("Tracked Frame", modifiableFrame);
        cv::waitKey(1);
    } catch (const cv::Exception& e) {
        std::cerr << "[VisionProcessor] Exception in imshow: " << e.what() << std::endl;
    }
}

// Predict method: Delegates the frame to the VisionBase implementation
void VisionProcessor::predict(const cv::Mat& frame) {
    vision->predict(frame);
}

// Draw method: Delegates the frame to the VisionBase implementation
void VisionProcessor::draw(cv::Mat& frame) {
    vision->draw(frame);
}

// Track method
void VisionProcessor::track() {
    
}
