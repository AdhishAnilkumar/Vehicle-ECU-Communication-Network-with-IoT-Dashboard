# Vehicle-ECU-Communication-Network-with-IoT-Dashboard
**Objective of the Project:** To build and demonstrate a Vehicle ECU communication network using CAN protocol with Iot Dashboard.<br>
**Apparatus Used:**
* 2 Arduino Unos
* ESP32 Dev Board
* Jumper Wires
* SSD1306 Screen
* 2 MCP2515 CAN Controllers
* SN65HVD230 CAN Transciever
* LED
* Resistor
* RFID Module
* Breadboards
* Accelerometer ADXL345<br>

**Tools Used**:Arduino Uno IDE,Blynk<br>
<br>
**Theory:**<br>
* **CAN Protocol**:CAN stands for Controller Acess Network.It is a robust, message-based serial communication protocol developed for real-time communication between multiple Electronic Control Units (ECUs) nodes over a shared communication bus. This protocol is usually inmplemented in Automobiles where several ECU or Electronic Control Units communicates each other.<br>

In this project the bus topology consists of 2 Arduino Unos and an ESP32 Dev Module where the Arduinos act as separate ECU nodes communicating to the ESP32 .Two wired (CAN_H and CAN_L) differential CAN bus is used to communicate  between the ECUs and ESP32.<br>

**ECU Description**<br>
* Arduino Uno 1: Airbag Deployment/Activation
  * Implemented using Accelerometer and LED to signal Airbag axtivation.
  * To demonstate crash,tap on the breadbaord
  * Via CAN the data is sent to ESP32 printing status on SSD1306 screen and notified on dashboard via Blynk.

* Arduino Uno 2: Security Lock
  * Uses RFID module acting as Security Lock for the vehicle.
  * If incorrect attempt found ,Vehichle remains closed and notifies on diashbaord via Blynk.
  * If correct entry, lock opens for 3 seconds and then closes.Required data sent via CAN bus.
<br>

**Circuit Setup**

  <img width="1600" height="1202" alt="Circuit Setup" src="https://github.com/user-attachments/assets/839d989e-60cc-4fd0-a558-9a5f1fe84da8" />

<br>

**Dashbaord **

<img width="346" height="757" alt="image" src="https://github.com/user-attachments/assets/9f107a9e-5fbb-448c-8b4a-ed53f811b9f4" />



  
  
  
  

  
  
