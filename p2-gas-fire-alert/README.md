# Project 2: Gas & Fire Safety Alert System

## Overview
This project detects gas leaks and fire using an MQ-2 Gas Sensor and a Flame Sensor. It provides visual and sound alerts with different safety levels.

## Components Used
- Arduino Uno R3
- MQ-2 Gas Sensor
- Flame Sensor
- Active Buzzer
- Red LED
- Yellow LED
- Green LED
- 220Ω Resistors
- Breadboard
- Jumper Wires

## Wiring Summary

### MQ-2 Gas Sensor
- VCC → 5V
- GND → GND
- AOUT → A0

### Flame Sensor
- VCC → 5V
- GND → GND
- DO → D7
- AO → A1 (optional)

### LEDs
- Green LED → D10
- Yellow LED → D11
- Red LED → D12

### Buzzer
- Positive → D9
- Negative → GND

## How to Run

1. Upload the Arduino code.
2. Power the Arduino.
3. Wait about 2 minutes for the MQ-2 sensor to warm up.
4. Open the Serial Monitor (9600 baud).
5. Test the gas sensor using LPG/smoke.
6. Test the flame sensor using a lighter or torch.
7. Observe LED, buzzer, and Serial Monitor output.

## Expected Output

- **SAFE**
  - Green LED ON
  - Buzzer OFF

- **WARNING**
  - Yellow LED ON
  - Slow beeping buzzer

- **GAS DANGER**
  - Red LED ON
  - Continuous buzzer

- **FIRE DANGER**
  - Red LED ON
  - Fast beeping buzzer

- **GAS + FIRE DANGER**
  - Red LED ON
  - Combined alarm pattern

## Serial Monitor Example

```
Gas Raw: 14 | GAS: 1% | FLAME: NONE | STATUS: SAFE

Gas Raw: 15 | GAS: 1% | FLAME: DETECTED | STATUS: FIRE DANGER
```

## Notes

- MQ-2 requires 1–2 minutes of warm-up after power-on.
- The flame sensor is active-low, so LOW means flame detected.
- The buzzer uses `millis()` for non-blocking alert patterns.
