🔥 Gas & Fire Safety Alert System

📌 Project Description

This project is a dual-sensor safety alert system built using Arduino Uno. It detects gas leakage using an MQ-2 gas sensor and fire/flame detection using a flame sensor. The system provides three alert levels using LEDs and a buzzer.

---

🛠 Components Used

- Arduino Uno R3
- MQ-2 Gas Sensor
- Flame Sensor
- Active Buzzer
- Green LED
- Yellow LED
- Red LED
- 220Ω Resistors
- Breadboard
- Jumper Wires
- USB Cable

---

🔌 Wiring Summary

MQ-2 Gas Sensor

Sensor Pin| Arduino Pin
VCC| 5V
GND| GND
AOUT| A0

Flame Sensor

Sensor Pin| Arduino Pin
VCC| 5V
GND| GND
DO| D7
AO| A1 (Optional)

LED Connections

Component| Arduino Pin
Green LED| D10
Yellow LED| D11
Red LED| D12

Buzzer

Buzzer Pin| Arduino Pin
Positive (+)| D9
Negative (-)| GND

---

▶️ How to Run

1. Connect all components according to the wiring diagram.
2. Open the Arduino IDE.
3. Select Arduino Uno board and correct COM port.
4. Upload the "gas_fire_alert.ino" code.
5. Power ON the Arduino.
6. Wait for MQ-2 sensor warm-up (1–2 minutes).
7. Open Serial Monitor with 9600 baud rate to view sensor status.

---

⚙ Working

- MQ-2 sensor reads gas concentration and converts it into percentage (0–100%).
- Flame sensor detects fire using active-low digital output.
- Arduino processes both sensor values and controls LEDs and buzzer.

Alert Levels:

Condition| Output
Gas < 30% and no flame| Green LED ON (SAFE)
Gas 30–60%| Yellow LED + Slow Beep (WARNING)
Gas > 60% or Flame detected| Red LED + Continuous Alarm (DANGER)

---

✅ Expected Output

Serial Monitor displays:

GAS: 20% | FLAME: NONE | STATUS: SAFE

GAS: 45% | FLAME: NONE | STATUS: WARNING

GAS: 80% | FLAME: NONE | STATUS: DANGER

GAS: 25% | FLAME: DETECTED | STATUS: DANGER

LED and buzzer behavior:

- 🟢 Green LED → Safe condition
- 🟡 Yellow LED + slow beep → Warning condition
- 🔴 Red LED + continuous buzzer → Danger condition

---

⚠ Notes

- MQ-2 sensor requires 1–2 minutes warm-up time after power ON.
- Flame sensor works on active-low logic:
  - LOW = Flame detected
  - HIGH = No flame detected

---
