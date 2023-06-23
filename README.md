# AI Obstacle Detection System using TensorFlow

This project implements an AI-based obstacle detection system using TensorFlow. It uses an ESP32-CAM module with a built-in Wi-Fi module and a trained TensorFlow model to detect obstacles in real-time.

## Description

The AI Obstacle Detection System captures images using the ESP32-CAM module's camera and performs inference using a TensorFlow Lite model to determine if an obstacle is present. If an obstacle is detected, the system adjusts the course accordingly.

The system consists of the following components:

- ESP32-CAM module: This module integrates a camera, Wi-Fi module, and GPIO pins for motor control.

- TensorFlow Lite: The trained TensorFlow model is converted into a lightweight TensorFlow Lite format for efficient inference on the ESP32-CAM.

- Image Preprocessing: The captured images are preprocessed by resizing, normalizing, and converting to grayscale to match the input requirements of the TensorFlow model.

- Inference: The preprocessed images are fed into the TensorFlow Lite model for inference, which produces a prediction indicating the presence or absence of an obstacle.

- Motor Control: If an obstacle is detected, the system adjusts the course by controlling the motors connected to the GPIO pins of the ESP32-CAM.

## Getting Started

To get started with the AI Obstacle Detection System, follow these steps:

1. Set up the ESP32-CAM module and connect the necessary components (camera, motors, etc.).

2. Train or obtain a TensorFlow model suitable for obstacle detection.

3. Convert the TensorFlow model to TensorFlow Lite format using the provided code.

4. Upload the converted model to the ESP32-CAM module (e.g., store it in an SD card).

5. Update the Arduino code with the necessary configurations (pins, Wi-Fi credentials, etc.) and implement the image preprocessing and inference using TensorFlow Lite.

6. Flash the Arduino code to the ESP32-CAM module.

7. Power on the system and observe the obstacle detection and course adjustment behavior.

## Contributions

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.
