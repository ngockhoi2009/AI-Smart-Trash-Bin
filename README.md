![AI Smart Trash Bin](completed-prototype.png)

# AI Smart Trash Bin

An independent project combining embedded systems, computer vision, and AI-powered waste classification.

## Demonstration

[Watch Project Demonstration](https://github.com/ngockhoi2009/AI-Smart-Trash-Bin/issues/1#issue-6225187403)

## Overview

This prototype explores how AI can interact with physical devices to automate waste sorting. It combines an ESP32, an ultrasonic sensor, an iPhone camera interface, and servo motors.

## How It Works

![System Workflow](system-workflow.png)

1. **Detection:** HC-SR04 detects an object.
2. **Image Capture:** ESP32 initiates image capture through an iPhone.
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

## Development Journey

**Step 1 – Hardware Setup**

Assembled the ESP32, HC-SR04 ultrasonic sensor, and two SG90 servo motors. Configured the power connections and GPIO assignments for object detection and servo control.

**Step 2 – ESP32 Firmware**

Developed the firmware in Arduino IDE to handle Wi-Fi connectivity, ultrasonic sensing, HTTP requests, and servo operations. Added detection guards to prevent repeated triggers.

**Step 3 – Camera Interface**

Built an HTML/JavaScript webpage to access the iPhone camera. Implemented a capture mechanism triggered by the ESP32 and image transmission to the backend.

**Step 4 – AI Backend**

Developed a Node.js server using Express.js and the Google GenAI SDK. Integrated the Gemini API to classify captured images and return results to the ESP32.

**Step 5 – System Integration & Testing**

Connected the hardware, camera interface, and backend into a complete workflow. Tested image transmission, classification responses, and servo movements, then debugged communication and triggering issues.

## Source Code

- [Arduino Firmware – IoTBin.ino](IoTBin.ino)
- [Node.js Backend – Server.js](Server.js)
- [Camera Interface – Web.html](Web.html)

## What I Learned

- Integrating hardware and software into one system.
- Connecting AI services with embedded devices.
- Debugging and testing a multidisciplinary project.

## AI Assistance

I independently implemented the firmware and backend, while using AI assistance to understand unfamiliar concepts and troubleshoot parts of the implementation. I tested and refined the code throughout development.

---

*An independent hands-on project exploring applied AI and embedded systems.*
