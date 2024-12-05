#include "server/processing/vision/implYolo.h"
#include <iostream>
#include <opencv2/dnn.hpp>
#include <map>
#include <cmath>

// Map of class IDs to vehicle names
const std::map<int, std::string> classIdToName = {
    {1, "bicycle"},
    {2, "car"},
    {3, "motorcycle"},
    {5, "bus"},
    {7, "truck"}
};

// Sigmoid function
float sigmoid(float x) {
    return 1.0f / (1.0f + exp(-x));
}

// Constructor: Load the YOLO model
SimpleVision::SimpleVision() {
    const std::string modelPath = "/home/fpauli/aif/git/AIFX009_Find_My_Bug/src/engine/server/processing/vision/models/yolo11m.onnx";
    net = cv::dnn::readNetFromONNX(modelPath);

    if (net.empty()) {
        std::cerr << "[SimpleVision] Failed to load model from: " << modelPath << std::endl;
        throw std::runtime_error("Model loading failed");
    }

    std::cout << "[SimpleVision] Model loaded successfully from: " << modelPath << std::endl;
}

Detections SimpleVision::detect(const cv::Mat& frame) {
    // Constants for input blob
    const int inputWidth = 640;
    const int inputHeight = 640;
    const float scaleFactor = 1.0 / 255.0;
    const cv::Scalar meanValues(0, 0, 0);
    const bool swapRB = true;

    // Create blob from the image
    cv::Mat blob = cv::dnn::blobFromImage(frame, scaleFactor, cv::Size(inputWidth, inputHeight), meanValues, swapRB, false);

    // Set the input blob
    net.setInput(blob);

    // Run inference
    std::vector<cv::Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());

    // Get output details
    int rows = outputs[0].size[1];
    int dimensions = outputs[0].size[2];
    bool isYoloV8 = false;

    if (dimensions > rows) { // Check if output shape matches YOLOv8
        isYoloV8 = true;     // At least YOLOv8 (can be YOLOv11)
        rows = outputs[0].size[2];
        dimensions = outputs[0].size[1];

        outputs[0] = outputs[0].reshape(1, dimensions);
        cv::transpose(outputs[0], outputs[0]);
    }

    float* data = (float*)outputs[0].data;

    float xFactor = static_cast<float>(frame.cols) / inputWidth;
    float yFactor = static_cast<float>(frame.rows) / inputHeight;

    // Initialize Detections
    Detections detections;

    // Loop through detections
    for (int i = 0; i < rows; ++i) {
        float confidence = isYoloV8 ? 0 : data[4];

        if (isYoloV8 || confidence >= 0.25) { // Confidence threshold
            float* classScores = isYoloV8 ? (data + 4) : (data + 5);
            cv::Mat scores(1, 80, CV_32F, classScores);
            cv::Point classIdPoint;
            double maxClassScore;

            cv::minMaxLoc(scores, 0, &maxClassScore, 0, &classIdPoint);

            if (maxClassScore > 0.45) { // Class score threshold
                confidence = isYoloV8 ? maxClassScore : (confidence * maxClassScore);

                float x = data[0];
                float y = data[1];
                float w = data[2];
                float h = data[3];

                int left = static_cast<int>((x - 0.5 * w) * xFactor);
                int top = static_cast<int>((y - 0.5 * h) * yFactor);
                int width = static_cast<int>(w * xFactor);
                int height = static_cast<int>(h * yFactor);

                detections.boxes.emplace_back(cv::Rect(left, top, width, height));
                detections.classIds.push_back(classIdPoint.x);
                detections.confidences.push_back(confidence);
            }
        }
        data += dimensions; // Move to the next anchor/detection
    }

    // Apply Non-Maximum Suppression (NMS)
    std::vector<int> indices;
    cv::dnn::NMSBoxes(detections.boxes, detections.confidences, 0.5, 0.4, indices);

    // Filter detections based on NMS and validate bounding box area
    Detections filteredDetections;

    // Define the maximum area limit for bounding boxes
    const int maxArea = 50000;

    for (int idx : indices) {
        const cv::Rect& box = detections.boxes[idx];
        int area = box.width * box.height;

        // Check if the bounding box area is greater than the limit
        if (area <= maxArea) {
            filteredDetections.boxes.push_back(box);
            filteredDetections.classIds.push_back(detections.classIds[idx]);
            filteredDetections.confidences.push_back(detections.confidences[idx]);

            // Add the class label to the new field
            std::string className = classIdToName.count(detections.classIds[idx])
                                    ? classIdToName.at(detections.classIds[idx])
                                    : "unknown";
            filteredDetections.labels.push_back(className);
        } else {
            std::cout << "....................[SimpleVision] Bounding box discarded. Area: " << area << std::endl;
        }
    }

    std::cout << "[SimpleVision] Detections completed. Objects detected: " << filteredDetections.boxes.size() << std::endl;

    return filteredDetections;

}


// Predict method: Placeholder
void SimpleVision::predict(const cv::Mat& frame) {
    (void)frame; // Suppress unused parameter warning
    // Future implementation here
}

// Draw method: Placeholder
void SimpleVision::draw(cv::Mat& frame) {
    (void)frame; // Suppress unused parameter warning
    // Future implementation here
}
