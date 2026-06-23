# 🚗 Car Black Box System using PIC16F877A

## 📌 Overview

The **Car Black Box System** is an embedded solution designed to monitor and record critical vehicle events along with precise timestamps. Inspired by aviation black boxes, this system ensures reliable storage and retrieval of event data for later analysis.

Developed using **Embedded C** on the **PIC16F877A microcontroller**, the system integrates multiple peripherals including **EEPROM, RTC, UART, CLCD Display, and Matrix Keypad** to provide a complete event logging and management interface.

---

## 🎯 Objective

The primary objective of this project is to design a robust embedded system capable of:

* Recording vehicle events with accurate timestamps
* Storing logs in non-volatile memory
* Providing secure access through password authentication
* Allowing users to view, clear, and download logs
* Simulating real-world embedded system architecture

---

## ✨ Features

### 🔹 Event Logging

* Captures vehicle events with real-time timestamps
* Maintains a rolling history of recent events
* Automatically updates logs during system operation

### 🔐 Password Authentication

* Secure login mechanism
* Prevents unauthorized access to system controls

### 📜 View Logs

* Displays stored logs on CLCD
* Allows navigation through event history

### 🧹 Clear Logs

* Erases all stored records
* Resets system for fresh logging

### ⏰ Set Time

* Modify RTC time
* Ensures accurate timestamp generation

### 🔑 Change Password

* Update system password securely
* Enhances access control

### 📡 Download Logs

* Transfers logs via UART
* Viewable on serial terminal

---

## 🛠️ Hardware Components

* PIC16F877A Microcontroller
* Character CLCD Display
* Matrix Keypad
* RTC Module
* EEPROM
* UART Interface
* Power Supply Circuit

---

## 💻 Software Tools

* MPLAB X IDE
* XC8 Compiler
* Embedded C
* Serial Terminal (UART Monitoring)

---

## 🏗️ System Architecture

```
Vehicle Events
      ↓
PIC16F877A Microcontroller
      ↓
RTC → Timestamp Generation
      ↓
EEPROM → Event Storage
      ↓
Menu System
      ↓
CLCD Display / UART Output
```

---

## ⚙️ Working Principle

1. Events are triggered via user interaction or system inputs
2. RTC provides the current timestamp
3. Event + timestamp stored in EEPROM
4. User logs in using password authentication
5. Menu-driven system allows:

   * Viewing logs
   * Clearing logs
   * Downloading logs via UART
6. System settings (time/password) can be updated

---

## 🧠 Key Concepts Applied

* Embedded C Programming
* State Machine Design
* EEPROM Interfacing
* UART Communication
* RTC Integration
* Menu-Driven UI Design
* CLCD Interfacing
* Matrix Keypad Handling
* Memory Management
* Event Logging Systems

---

## ⚠️ Challenges & Solutions

* **Keypad Debouncing Issue** → Handled using delay & state logic
* **Menu Navigation Bugs** → Improved using structured state machine
* **EEPROM Data Handling** → Optimized indexing & storage logic
* **UART Debugging** → Verified baud rate & transmission flow
* **RTC Sync Issues** → Ensured proper initialization and update flow
* **System Stability** → Refined testing and modular debugging

---

## 📚 Learning Outcomes

* Strong understanding of embedded system design
* Hands-on experience with PIC16F877A
* EEPROM data management techniques
* UART communication debugging
* Real-time system development
* Secure system design using authentication
* Practical problem-solving in embedded applications

---

## 🚀 Future Enhancements

* SD Card-based storage
* Sensor integration (speed, impact detection)
* CAN protocol support
* GPS-based tracking
* PC dashboard for monitoring
* Advanced encryption for security

---

## 📸 Project Demonstration

Include screenshots or videos for:

* Event Logging Interface
* Login System
* Log Viewing
* Time Setting
* Password Change
* UART Log Output

---

## 📌 Conclusion

This project successfully demonstrates a **real-time embedded event logging system** using the PIC16F877A microcontroller. By integrating multiple peripherals and communication interfaces, it provides a practical and scalable solution for monitoring, storing, and retrieving vehicle-related events.

It also reflects strong fundamentals in **embedded programming, system design, and debugging**, making it a valuable hands-on project for real-world applications.

---
