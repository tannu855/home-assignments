# Project 1 - Smart Room Climate Monitor

## Components Used
- ESP32 Dev Board
- DHT11 Temperature and Humidity Sensor
- OLED Display (SSD1306 I2C)
- Active Buzzer
- Red LED
- Green LED
- 220Ω Resistors
- Breadboard
- Jumper Wires

## Wiring Summary

DHT11
- VCC → 3.3V
- GND → GND
- DATA → GPIO4

OLED
- VCC → 3.3V
- GND → GND
- SDA → GPIO21
- SCL → GPIO22

Red LED → GPIO25

Green LED → GPIO26

Buzzer → GPIO27

## Libraries Used
- DHTesp
- Adafruit GFX
- Adafruit SSD1306

## How to Run
1. Connect the hardware as per the wiring.
2. Open the .ino file in Arduino IDE.
3. Select ESP32 Dev Module.
4. Upload the code.
5. Open Serial Monitor at 115200 baud.

## Expected Output
- OLED displays temperature and humidity.
- Green LED glows during normal conditions.
- Red LED and buzzer activate when temperature is above 38°C or humidity is above 80%.
- CSV data is printed on the Serial Monitor every 5 seconds.
