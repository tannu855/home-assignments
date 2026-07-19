# Smart Plant Monitoring & Automatic Watering System

## Project Overview
This project is an IoT-based Smart Plant Monitoring System using ESP32. It monitors soil moisture, temperature, and humidity, displays the readings on an OLED display, and automatically controls a water pump (simulated using a relay and LED). A manual override button allows watering for 5 seconds.

---

## Components Used
- ESP32 Dev Board
- Capacitive Soil Moisture Sensor
- DHT22 Temperature & Humidity Sensor
- 2-Channel Relay Module
- 0.96" I2C OLED Display
- Red LED
- Green LED
- Active Buzzer
- Push Button
- Breadboard
- Jumper Wires

---

## Wiring Summary

| Component | ESP32 Pin |
|-----------|-----------|
| Soil Moisture Sensor (AOUT) | GPIO34 |
| DHT22 Data | GPIO4 |
| Relay IN1 | GPIO26 |
| Push Button | GPIO25 |
| Green LED | GPIO18 |
| Red LED | GPIO19 |
| Buzzer | GPIO23 |
| OLED SDA | GPIO21 |
| OLED SCL | GPIO22 |

---

## Sensor Calibration

- Dry Value: **3200**
- Wet Value: **1200**

---

## Soil Status

- DRY : Moisture < 30%
- OPTIMAL : 30% - 70%
- WET : > 70%

Pump turns ON below 30% and turns OFF above 40% using hysteresis.

---

## Features

- Soil moisture monitoring
- Temperature and humidity monitoring
- Automatic watering using relay
- Manual watering button (5 seconds)
- OLED display with moisture bar graph
- Buzzer alert in DRY condition
- Serial Monitor output

---

## How to Run

1. Connect all components as per wiring.
2. Open the Arduino code in Arduino IDE.
3. Install required libraries:
   - Adafruit GFX
   - Adafruit SSD1306
   - DHT Sensor Library
4. Select ESP32 board and correct COM port.
5. Upload the code.
6. Open Serial Monitor at **115200 baud**.

---

## Expected Output

- OLED displays soil moisture, temperature, humidity, and soil status.
- Relay turns ON when moisture is below 30%.
- Relay turns OFF when moisture is above 40%.
- Green LED indicates OPTIMAL/WET condition.
- Red LED and buzzer indicate DRY condition.
- Manual button activates watering for 5 seconds.
- Serial Monitor continuously displays sensor readings.

---

## Sample Serial Output

```
Raw: 4095  Moisture: 0%  Temp: 32.80 C  Humidity: 75.60%  Status: DRY

Raw: 699  Moisture: 100%  Temp: 32.80 C  Humidity: 75.10%  Status: WET
```



