#include "server/processing/vision/implYolo.h"
#include <iostream>
#include <opencv2/dnn.hpp>

// Constructor: Load the YOLO model
SimpleVision::SimpleVision() {
    const std::string modelPath = "/home/fpauli/aif/git/AIFX009_Find_My_Bug/src/engine/server/processing/vision/models/yolo11n.onnx";
    net = cv::dnn::readNetFromONNX(modelPath);

    if (net.empty()) {
        std::cerr << "[SimpleVision] Failed to load model from: " << modelPath << std::endl;
        throw std::runtime_error("Model loading failed");
    }

    std::cout << "[SimpleVision] Model loaded successfully from: " << modelPath << std::endl;
}

// Implementation of detect: Detects vehicles and draws bounding boxes
void SimpleVision::detect(const cv::Mat& frame) {
    // Preprocess the frame for YOLO
    const int inputWidth = 640; // YOLO input width
    const int inputHeight = 640; // YOLO input height
    const float scaleFactor = 1.0 / 255.0;
    const cv::Scalar meanValues(0, 0, 0); // No mean subtraction
    const bool swapRB = true;

    cv::Mat blob = cv::dnn::blobFromImage(frame, scaleFactor, cv::Size(inputWidth, inputHeight), meanValues, swapRB, false);

    // Set the blob as input to the network
    net.setInput(blob);

    // Forward pass to get the detection results
    std::vector<cv::Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());

    // Post-process detections
    float confidenceThreshold = 0.5;
    float nmsThreshold = 0.4; // Non-max suppression threshold
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    for (const auto& output : outputs) {
        for (int i = 0; i < output.rows; i++) {
            const auto* data = output.ptr<float>(i);
            float confidence = data[4]; // Objectness confidence
            if (confidence > confidenceThreshold) {
                // Extract class scores
                cv::Mat scores = output.row(i).colRange(5, output.cols);
                cv::Point classIdPoint;
                double maxClassScore;
                cv::minMaxLoc(scores, 0, &maxClassScore, 0, &classIdPoint);

                if (maxClassScore > confidenceThreshold) {
                    int centerX = static_cast<int>(data[0] * frame.cols);
                    int centerY = static_cast<int>(data[1] * frame.rows);
                    int width = static_cast<int>(data[2] * frame.cols);
                    int height = static_cast<int>(data[3] * frame.rows);
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    classIds.push_back(classIdPoint.x);
                    confidences.push_back(static_cast<float>(maxClassScore));
                    boxes.emplace_back(left, top, width, height);
                }
            }
        }
    }

    // Apply non-max suppression to filter overlapping boxes
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, confidenceThreshold, nmsThreshold, indices);

    // Draw the boxes on the image
    for (int idx : indices) {
        cv::Rect box = boxes[idx];
        cv::rectangle(frame, box, cv::Scalar(0, 255, 0), 2);

        std::string label = "Vehicle: " + std::to_string(classIds[idx]) + " (" + std::to_string(confidences[idx]) + ")";
        int baseline;
        cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
        int top = std::max(box.y, labelSize.height);
        cv::rectangle(frame, cv::Point(box.x, top - labelSize.height),
                      cv::Point(box.x + labelSize.width, top + baseline), cv::Scalar(0, 255, 0), cv::FILLED);
        cv::putText(frame, label, cv::Point(box.x, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);
    }

    // Display the frame with detections
    cv::imshow("Vehicle Detector - YOLO", frame);
    std::cout << "[SimpleVision] Frame processed with YOLO detections." << std::endl;
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
