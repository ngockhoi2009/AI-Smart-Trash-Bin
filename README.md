![AI Smart Trash Bin](completed-prototype.png)

# AI Smart Trash Bin

An independent project combining embedded systems with AI-powered image classification to explore automated waste sorting.

## Demonstration

[Watch Project Demonstration](https://github.com/ngockhoi2009/AI-Smart-Trash-Bin/issues/1#issue-6225187403)

## Overview

This prototype explores how AI can interact with physical devices to automate waste sorting. It combines an ESP32, an ultrasonic sensor, an iPhone camera interface, and servo motors.

## How It Works

![System Workflow](system-workflow.png)

1. **Detection:** HC-SR04 detects an object.
2. **Image Capture:** The iPhone camera interface captures an image when triggered by the ESP32.
3. **Classification:** A Node.js server sends the image to Google Gemini API.
4. **Sorting:** ESP32 receives the result and controls two servo motors.

## Hardware & Technologies

- **Hardware:** ESP32, HC-SR04, 2 SG90 servo motors
- **Backend:** Node.js, Express.js
- **AI:** Google Gemini API
- **Languages:** C++, JavaScript, HTML
- **Communication:** HTTP, JSON

## Circuit Design

![Circuit Diagram](circuit_image.png)

![Assembly Wiring](assembly-wiring.jpg)

## Development Journey

**Step 1 – Hardware Setup**

Assembled the ESP32, HC-SR04 ultrasonic sensor, and two SG90 servo motors. Configured the power connections and GPIO assignments for object detection and servo control.

**Step 2 – AI Backend**

Developed a Node.js server using Express.js and the Google GenAI SDK. Integrated the Gemini API to classify captured images and return results to the ESP32.

**Step 3 – Camera Interface**

Built an HTML/JavaScript webpage to access the iPhone camera. Implemented a capture mechanism triggered by the ESP32 and image transmission to the backend.

**Step 4 – ESP32 Firmware**

Developed the firmware in Arduino IDE to handle Wi-Fi connectivity, ultrasonic sensing, HTTP requests, and servo operations. Added detection guards to prevent repeated triggers.

**Step 5 – System Integration & Testing**

Connected the hardware, camera interface, and backend into a complete workflow. Tested image transmission, classification responses, and servo movements, then debugged communication and triggering issues.

## Source Code

- [Arduino Firmware – IoTBin.ino](IoTBin.ino)
- [Node.js Backend – Server.js](Server.js)
- [Camera Interface – Web.html](Web.html)

## What I Learned

- Integrating embedded hardware, backend services, and web interfaces into a working system.
- Connecting cloud-based AI services with microcontrollers through HTTP and JSON.
- Debugging communication, sensor triggering, and hardware-software integration issues.

## AI Assistance

I used AI assistance during development, particularly for building the HTML/JavaScript camera interface and troubleshooting. I implemented the Node.js backend and Arduino firmware, then integrated and tested all components to make the complete system work together.

---

*An independent hands-on project exploring applied AI and embedded systems.*
