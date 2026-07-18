# Gas & Fire Safety Alert System 🚨

## Project Overview
The Gas & Fire Safety Alert System is an IoT-based safety device that detects gas leakage and fire simultaneously using an MQ-2 gas sensor and a flame sensor. The system provides three alert levels using LEDs and a buzzer to improve home safety.

## Objective
To design a safety monitoring system that can:
- Detect LPG/gas leakage
- Detect fire/flame
- Provide visual and audio alerts
- Display real-time status through Serial Monitor

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

## Circuit Connections

### MQ-2 Gas Sensor
| MQ-2 Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| AOUT | A0 |

### Flame Sensor
| Flame Sensor Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| DO | D7 |
| AO | A1 (Optional) |

### Output Devices
| Component | Arduino Pin |
|---|---|
| Green LED | D10 |
| Yellow LED | D11 |
| Red LED | D12 |
| Buzzer | D9 |

## Working Principle

1. The MQ-2 sensor continuously measures gas concentration.
2. The gas value is converted into percentage (0-100%).
3. The flame sensor detects fire using its digital output.
4. According to the sensor values, the system shows three alert levels:

### Alert Levels

| Condition | Output |
|---|---|
| Gas < 30% and no flame | SAFE - Green LED |
| Gas 30-60% | WARNING - Yellow LED + Slow Beep |
| Gas > 60% or Flame detected | DANGER - Red LED + Continuous Alarm |

## Flame Sensor Logic
The flame sensor used in this project is active-low.

- Digital Output LOW = Flame detected
- Digital Output HIGH = No flame detected

## MQ-2 Warm-up Requirement
The MQ-2 gas sensor requires 1-2 minutes of warm-up time after powering ON because its sensing element needs time to stabilize and provide accurate readings.

## Serial Monitor Output Example

GAS: 45% | FLAME: NONE | STATUS: WARNING

GAS: 80% | FLAME: NONE | STATUS: DANGER

GAS: 20% | FLAME: DETECTED | STATUS: DANGER

## Features
- Dual sensor safety monitoring
- Independent gas and flame detection
- Three-level alert system
- Real-time Serial Monitor updates
- Non-blocking buzzer control using millis()

## Future Improvements
- Add a silence button
- Send mobile notifications
- Add IoT cloud monitoring
