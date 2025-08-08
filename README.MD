

# Victural Req

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com)
[![Version](https://img.shields.io/badge/version-1.0.0-blue)](https://github.com)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A powerful CLI tool to delegate HTTP requests to your MCU over a high-speed serial connection.

---

### **Our Mission**
Victural Req allows you to send HTTP requests from your computer, but delegates the actual task to a connected Microcontroller Unit (MCU). This is perfect for IoT projects, home automation, testing network endpoints from a specific hardware device, or any scenario where you need to bridge your local development environment with a hardware-based network client.

### **Key Features**
*   **High-Speed Communication:** Optimized for baud rates up to 500,000 for rapid data exchange.
*   **Simple CLI Interface:** Send requests with a single, straightforward command.
*   **Robust & Stable:** Built with C++ on the MCU side for maximum stability and performance.
*   **Professional Workflow:** Utilizes PlatformIO for superior dependency management and a streamlined development process.

### **How It Works**

The architecture is simple. Your computer runs a Node.js script that communicates with the MCU over a serial (USB) connection. The MCU receives the target URL, performs the HTTP request over Wi-Fi, and sends the response back to the Node.js script.

```
+--------------------------+          +-------------------------+          +------------------------+
|                          |          |                         |          |                        |
|  Your PC (Node.js CLI)   |  ----->  |   MCU (ESP8266/ESP32)   |  ----->  |   The Internet / API   |
|                          | (Serial) |                         |  (Wi-Fi) |                        |
+--------------------------+          +-------------------------+          +------------------------+
```

### ❗ Important: PlatformIO is Required

This project is built using **PlatformIO** and is **not compatible with the Arduino IDE**.

We chose PlatformIO for its superior dependency management, professional development environment, and advanced configuration options, which are essential for the stability and performance of this project. Using the Arduino IDE will result in compilation errors and unexpected behavior.

### **Prerequisites**

#### Hardware
*   An ESP8266 or ESP32 based board.
*   A Micro-USB cable for programming and communication.

#### Software
*   [Node.js](https://nodejs.org/) (v16+ recommended).
*   [PlatformIO Core (CLI)](https://platformio.org/install/cli) or [PlatformIO IDE for VS Code](https://platformio.org/install/ide?install=vscode).

### **Installation**

#### 1. MCU (Firmware) Setup
1.  Clone this repository: `git clone https://your-repo-url.com/victural-req.git`
2.  Open the project folder in Visual Studio Code with the PlatformIO extension installed.
3.  Modify the `platformio.ini` file if needed to match your specific board.
4.  Modify the `src/main.cpp` file to include your Wi-Fi credentials.
5.  Build and upload the firmware to your MCU using the PlatformIO interface (click the "Upload" arrow button).

#### 2. CLI (Node.js) Setup
1.  Navigate to the `cli` directory in your terminal: `cd victural-req/cli`
2.  Install the required Node.js packages:
    ```bash
    npm install
    ```

### **Usage**

The CLI tool takes a single argument: the full URL you want the MCU to send a GET request to.

From inside the `cli` directory, run the command:

```bash
node . "http://your-target-url.com"
```

#### Example

```bash
node . "https://jsonplaceholder.typicode.com/todos/1"
```

**Expected Output:**
```
Connecting to port 'COM3' at baud rate 500000...
----------------------------------------------------
 SUCCESS: Port opened. Hardware Flow Control ENABLED.
----------------------------------------------------
COMMAND SENT: https://jsonplaceholder.typicode.com/todos/1
Waiting for response from device...

--- FINAL RESPONSE RECEIVED ---
RAW LINE: {"code":200,"data":"ewogICJ1c2VySWQiOiAxLAogICJpZCI6IDEsCiAgInRpdGxlIjogImRlbGVjdHVzIGF1dCBhdXRlbSIsCiAgImNvbXBsZXRlZCI6IGZhbHNlCn0="}
PARSED JSON: {
  code: 200,
  data: 'ewogICJ1c2VySWQiOiAxLAogICJpZCI6IDEsCiAgInRpdGxlIjogImRlbGVjdHVzIGF1dCBhdXRlbSIsCiAgImNvbXBsZXRlZCI6IGZhbHNlCn0='
}
STATUS: Success!
DECODED DATA:
 {
  "userId": 1,
  "id": 1,
  "title": "delectus aut autem",
  "completed": false
}
--------------------------
```

### **Tech Stack**

*   **[Node.js](https://nodejs.org/):** Powers the command-line interface (CLI) on the host computer.
*   **[PlatformIO](https://platformio.org/):** Used for a professional and reliable MCU development environment.
*   **[C++](https://isocpp.org/):** The language of choice for writing stable, high-performance firmware for the MCU.