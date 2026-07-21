Project 1: Smart Room Climate Monitor

Objective

Build a smart room climate monitoring system using ESP32, DHT sensor, OLED display, LEDs, and a buzzer. The system continuously measures temperature and humidity, displays the readings on an OLED screen, and alerts the user when the room becomes too hot or humid.

Components Used 

- ESP32 Dev Board
- DHT Temperature & Humidity Sensor
- OLED Display (SSD1306 I2C)
- Red LED
- Green LED
- Active Buzzer
- Breadboard
- Jumper Wires

Wiring Summary

- DHT Sensor DATA → GPIO2
- OLED SDA → GPIO21
- OLED SCL → GPIO22
- Red LED → GPIO8
- Green LED → GPIO9
- Buzzer → GPIO10
- VCC → 3.3V
- GND → GND

Libraries Used

- Wire
- Adafruit GFX
- Adafruit SSD1306
- DHT

How to Run

1. Connect all components according to the wiring.
2. Install the required libraries in Arduino IDE.
3. Upload the code to the ESP32.
4. Open the Serial Monitor at 115200 baud.
5. Observe the OLED display and alert system.

Expected Output

- OLED displays temperature and humidity.
- Climate status is shown as COOL, COMFORT, HOT, or DANGER.
- Green LED remains ON during normal conditions.
- Red LED and buzzer activate when temperature exceeds 38°C or humidity exceeds 80%.
- Serial Monitor logs data in CSV format every 5 seconds.
- OLED cycles to display maximum and minimum recorded temperature.

Wokwi Simulation

https://wokwi.com/projects/470130973666428929

