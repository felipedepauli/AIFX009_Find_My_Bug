from ultralytics import YOLO
import argparse

# Arguments
parser = argparse.ArgumentParser()
parser.add_argument('weights', type=str, help='path to model.pt')

# Load the YOLO model
model = YOLO(parser.parse_args().weights)

# Export the model to ONNX format
model.export(format="onnx", imgsz=[640,640], opset=12)