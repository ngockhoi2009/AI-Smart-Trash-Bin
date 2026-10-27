# AI-Smart-Trash-Bin
An embedded AI project exploring the integration of ESP32, computer vision, and automated waste sorting.
## Demonstration

[*Watch the Project Demonstration*]
(https://drive.google.com/file/d/1eQrgix22_SPGAshmd_g9ONcijUHg3q8C/view?usp=sharing)

## Project Gallery

![Project Photo 1](P1.jpg)
![Project Photo 2](P2.jpg)
![Project Photo 3](P3.jpg)

## System Architecture

The prototype integrates embedded hardware, image capture, and AI-powered classification to automate waste sorting.
1. Object Detection: The HC-SR04 ultrasonic sensor detects an object near the bin.
2. Image Capture: The ESP32 initiates the image-capture workflow through an iPhone.
3. AI Classification: The captured image is sent to a Node.js server, which uses the Gemini API to classify the waste.
4. Hardware Control: The ESP32 processes the classification result and controls two servo motors to perform the sorting action.

## Hardware & Technologies

- Microcontroller: ESP32
- Distance Sensor: HC-SR04 ultrasonic sensor
- Actuators: Two servo motors
- Image Capture: iPhone camera interface
- Backend: Node.js and Express.js
- AI Service: Google Gemini API
- Communication: HTTP and JSON
- Programming Languages: C++ and JavaScript

## Source Code

- **Arduino Firmware (C++):** [View Code](./IoTBin.ino)
- **Node.js Backend:** [View Code](./Server.js)
- **HTML Camera Interface:** [View Code](./Web.html)

## Key Learning Outcomes

- Integrating electronic components into a working prototype
- Connecting hardware with an AI-powered workflow
- Exploring the interaction between software decisions and physical actions
- Testing and troubleshooting a multidisciplinary engineering project

## Development Process & AI Assistance

I independently implemented the Arduino firmware and developed the Node.js backend, using AI assistance mainly for HTTP communication and JSON handling. Throughout the project, I tested and refined the code to ensure reliable communication between the ESP32 and the server. I am continuing to study these concepts to strengthen my understanding and gradually improve my ability to implement the system independently.

---

*An independent hands-on project exploring applied AI and embedded systems.*
