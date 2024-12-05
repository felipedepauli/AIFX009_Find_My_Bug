#ifndef SIMPLEVISION_H
#define SIMPLEVISION_H

#include "VisionBase.h"
#include <opencv2/dnn.hpp>
#include <string>

class SimpleVision : public VisionBase {
private:
    cv::dnn::Net net; // Store the model as a member variable

public:
    SimpleVision(); // Default constructor

    Detections detect(const cv::Mat& frame) override;
    void predict(const cv::Mat& frame) override;
    void draw(cv::Mat& frame) override;
};

#endif // SIMPLEVISION_H
