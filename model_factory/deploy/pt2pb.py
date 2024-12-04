from ultralytics import YOLO
import argparse

# Arguments
parser = argparse.ArgumentParser()
parser.add_argument('weights', type=str, help='path to model.pt')

# Carregar o modelo YOLO
model = YOLO(parser.parse_args().weights)

# Exportar para formato TensorFlow (.pb)
model.export(format='saved_model')
