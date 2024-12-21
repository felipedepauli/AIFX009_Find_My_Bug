#ifndef VISIONBASE_H
#define VISIONBASE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <unordered_map>

typedef struct Detections {
    std::vector<cv::Rect> boxes;           // Bounding boxes
    std::vector<int> classIds;            // Integer class IDs
    std::vector<float> confidences;       // Confidence scores
    std::vector<std::string> labels;      // Class names (e.g., "car", "truck")
    std::unordered_map<int, size_t> idToIndex; // Map from trackId to original detection index
} Detections;

class VisionBase {
public:
    virtual ~VisionBase() = default;

    // Method to detect objects in a frame
    virtual Detections detect(const cv::Mat& frame) = 0;

    // Placeholder methods for further implementation
    virtual void predict(const cv::Mat& frame) = 0;
    virtual void draw(cv::Mat& frame) = 0;
};

#endif // VISIONBASE_H
