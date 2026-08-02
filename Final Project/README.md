# Smart Bank Locker Security System

## Project Overview
The Smart Bank Locker Security System is an IoT-based security project that uses two ESP32 boards for secure locker authentication. The user's PIN is encrypted before wireless transmission and decrypted only at the receiver side. This improves security and helps prevent unauthorized access.

## Components Used
- 2 × ESP32 Development Boards
- 4×4 Matrix Keypad
- SG90 Servo Motor
- Red LED
- Green LED
- Piezo Buzzer
- Breadboard
- Jumper Wires
- USB Cable

## Setup and Installation
1. Connect all components according to the circuit diagram.
2. Upload the transmitter code to the first ESP32.
3. Upload the receiver code to the second ESP32.
4. Power both ESP32 boards.
5. Enter the PIN using the keypad to test the system.

## Working Methodology
1. The user enters the PIN using the keypad.
2. The first ESP32 encrypts the PIN.
3. The encrypted PIN is sent wirelessly to the second ESP32.
4. The second ESP32 decrypts and verifies the PIN.
5. If the PIN is correct, the servo motor unlocks the locker and the green LED turns ON.
6. If the PIN is incorrect, the locker remains locked, the red LED turns ON, and the buzzer sounds.

## Team Members
- Tannu
- Mukul Bindal

## Additional Information
This project demonstrates secure wireless communication using a dual ESP32 architecture. It improves the security of a traditional bank locker by transmitting encrypted PIN data instead of plain text.
