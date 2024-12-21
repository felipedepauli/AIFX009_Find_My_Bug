#include "VisionProcessor.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

// Constructor: Initializes with a SimpleVision and TrackingProcessor instance
VisionProcessor::VisionProcessor()
    : vision(std::make_unique<SimpleVision>()),
      tracking(std::make_unique<TrackingProcessor>()),
      frameCounter(0) {}

// Detect method: Delegates the frame to the VisionBase implementation
void VisionProcessor::detect(const cv::Mat& frame) {
    // Performs detection with the original frame (const)
    Detections detections = vision->detect(frame);

    // Creates a copy to modify
    cv::Mat modifiableFrame = frame.clone();

    // Updates tracking and draws the bounding boxes on the copy
    tracking->updateDetections(detections, modifiableFrame);

    // Get the frame name for both image and json file
    std::string frameName = "/workspace/results/detection_" + std::to_string(frameCounter);
    std::string imageFilename = frameName + ".jpg";
    std::string jsonFilename = frameName + ".json";

    try {
        // Save the image in the directory
        cv::imwrite(imageFilename, modifiableFrame);

        // Create the JSON containing the information of the detected objects
        nlohmann::json jsonData;
        jsonData["frame"] = frameName;
        jsonData["detections"] = nlohmann::json::array();  // Array of detections

        // Loop to add the information of each detection
        for (size_t i = 0; i < detections.boxes.size(); ++i) {
            nlohmann::json detectionJson;
            detectionJson["id"] = i;  // Incremental ID (can be changed)
            detectionJson["class_id"] = detections.classIds[i];  // Class of the detected object
            detectionJson["confidence"] = detections.confidences[i];  // Prediction confidence

            // Add the bounding box in the format [x, y, width, height]
            const cv::Rect& box = detections.boxes[i];
            detectionJson["bounding_box"] = {
                {"x", box.x},
                {"y", box.y},
                {"width", box.width},
                {"height", box.height}
            };

            jsonData["detections"].push_back(detectionJson);
        }

        // Save the JSON file
        std::ofstream jsonFile(jsonFilename);
        if (jsonFile.is_open()) {
            jsonFile << jsonData.dump(4);  // Indent with 4 spaces
            jsonFile.close();
            std::cout << "[VisionProcessor  ] JSON file saved: " << jsonFilename << std::endl;
        } else {
            std::cerr << "[ERROR] Could not open JSON file for writing: " << jsonFilename << std::endl;
        }

        frameCounter++;  // Increment the frame for the next image
    } catch (const cv::Exception& e) {
        std::cerr << "[VisionProcessor  ] Exception in imwrite or json creation: " << e.what() << std::endl;
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
