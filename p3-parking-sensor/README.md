# Project 3: Ultrasonic Parking Assistant

## Overview
This project simulates a real car parking assistant using an HC-SR04 Ultrasonic Sensor. The system measures the distance of nearby objects and provides visual and audio alerts using LEDs, a buzzer, and an OLED display.

## Components Used
- Arduino Uno R3
- HC-SR04 Ultrasonic Sensor
- OLED Display (0.96" I2C)
- Active Buzzer
- Green LED
- Yellow LED
- Red LED
- 220Ω Resistors
- Breadboard
- Jumper Wires

## Wiring Summary
- HC-SR04 VCC → 5V
- HC-SR04 GND → GND
- HC-SR04 TRIG → Pin 9
- HC-SR04 ECHO → Pin 10
- Green LED → Pin 4
- Yellow LED → Pin 5
- Red LED → Pin 6
- Buzzer → Pin 3
- OLED SDA → A4
- OLED SCL → A5

## How to Run
1. Connect all components as per the wiring.
2. Upload the Arduino code.
3. Open the Serial Monitor (9600 baud).
4. Move an object closer or farther from the ultrasonic sensor.
5. Observe the OLED display, LEDs, buzzer, and Serial Monitor output.

## Expected Output
- OLED displays the distance in centimeters with a proximity bar graph.
- Serial Monitor prints the distance and current zone every 500 ms.
- **SAFE (>30 cm):** Green LED ON, no buzzer.
- **CAUTION (21–30 cm):** Yellow LED ON, beep every 800 ms.
- **CLOSE (11–20 cm):** Yellow + Red LEDs ON, beep every 300 ms.
- **DANGER (≤10 cm):** Red LED ON with continuous buzzer.


