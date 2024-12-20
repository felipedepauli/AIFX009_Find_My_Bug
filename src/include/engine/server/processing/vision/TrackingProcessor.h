#ifndef TRACKING_PROCESSOR_H
#define TRACKING_PROCESSOR_H

#include "ByteTrack/BYTETracker.h"
#include <memory>
#include <iostream>
#include <unordered_map>
#include <map>

// Map of class IDs to vehicle names
const std::map<int, std::string> classIdToName = {
    {1, "bicycle"},
    {2, "car"},
    {3, "motorcycle"},
    {5, "bus"},
    {7, "truck"}
};

class TrackingProcessor {
private:
    byte_track::BYTETracker tracker;
    std::unordered_map<int, size_t> trackIdToDetectionIdx; // Maps trackId to detection index

public:
    TrackingProcessor() : tracker(20) {
        std::cout << "[TrackingProcessor] Initialized with 20 FPS" << std::endl;
    }

    ~TrackingProcessor() {
        // cv::destroyAllWindows();
    }

    void updateDetections(const Detections& detections, cv::Mat& frame) {

        // Clear previous mappings
        trackIdToDetectionIdx.clear();

        // Convert Detections to objects compatible with BYTETracker
        std::vector<byte_track::Object> objects;
        for (size_t i = 0; i < detections.boxes.size(); ++i) {
            // Convert cv::Rect to byte_track::Rect<float>
            byte_track::Rect<float> rect(
                static_cast<float>(detections.boxes[i].x),
                static_cast<float>(detections.boxes[i].y),
                static_cast<float>(detections.boxes[i].width),
                static_cast<float>(detections.boxes[i].height)
            );

            // Create ByteTrack object
            objects.emplace_back(rect, detections.classIds[i], detections.confidences[i]);
        }

        // Update BYTETracker with detected objects
        std::vector<byte_track::BYTETracker::STrackPtr> trackedObjects = tracker.update(objects);

        // Map track IDs to detection indices
        for (size_t i = 0; i < trackedObjects.size(); ++i) {
            int trackId = static_cast<int>(trackedObjects[i]->getTrackId());
            trackIdToDetectionIdx[trackId] = i;
        }

        // Draw bounding boxes with IDs on the frame
        for (const auto& trackedObj : trackedObjects) {
            const auto& bbox = trackedObj->getRect();
            int trackId = static_cast<int>(trackedObj->getTrackId());

            // Retrieve the original detection index
            if (trackIdToDetectionIdx.count(trackId)) {
                size_t detectionIdx = trackIdToDetectionIdx[trackId];

                // Retrieve corresponding class and confidence
                std::string classLabel = "Unknown";
                if (detectionIdx < detections.classIds.size() &&
                    classIdToName.count(detections.classIds[detectionIdx])) {
                    classLabel = classIdToName.at(detections.classIds[detectionIdx]);
                }

                float confidence = 0.0f;
                if (detectionIdx < detections.confidences.size()) {
                    confidence = detections.confidences[detectionIdx];
                }

                // Convert byte_track::Rect<float> to cv::Rect
                cv::Rect cv_bbox(
                    static_cast<int>(bbox.x()),
                    static_cast<int>(bbox.y()),
                    static_cast<int>(bbox.width()),
                    static_cast<int>(bbox.height())
                );

                // Draw bounding box
                cv::rectangle(frame, cv_bbox, cv::Scalar(0, 255, 0), 2);

                // Assemble text in two lines
                std::string idText = "ID: " + std::to_string(trackId);
                std::string classText = classLabel + " (" + cv::format("%.2f", confidence) + ")";

                // Calculate text position
                int baseline = 0;
                cv::Size idTextSize = cv::getTextSize(idText, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
                cv::Size classTextSize = cv::getTextSize(classText, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);

                int top = std::max(cv_bbox.y - idTextSize.height - classTextSize.height - baseline, 0);
                int left = std::max(cv_bbox.x, 0);

                // Draw background for the text
                cv::rectangle(frame,
                              cv::Point(left, top),
                              cv::Point(left + std::max(idTextSize.width, classTextSize.width), top + idTextSize.height + classTextSize.height + baseline),
                              cv::Scalar(0, 255, 0), cv::FILLED);

                // Draw ID
                cv::putText(frame, idText,
                            cv::Point(left, top + idTextSize.height),
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 2);

                // Draw Class and Confidence
                cv::putText(frame, classText,
                            cv::Point(left, top + idTextSize.height + classTextSize.height),
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1);
            }
        }

        std::cout << "[TrackingProcessor] Tracking completed. Number of tracked objects: " << trackedObjects.size() << std::endl;
    }
};

#endif // TRACKING_PROCESSOR_H
