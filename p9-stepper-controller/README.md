Project 9: Stepper Motor Precision Positioner

Objective

This project implements a precision stepper motor positioning system using an Arduino Uno and a 28BYJ-48 stepper motor with a ULN2003 driver. A potentiometer is used to set the target angle (0°–360°), while push buttons allow clockwise, counter-clockwise, and home position control. An SPI OLED display shows the current position, target position, motor direction, and step count in real time.

---

Components Used

- Arduino Uno R3
- 28BYJ-48 Stepper Motor
- ULN2003 Stepper Motor Driver
- OLED Display (SSD1306 SPI, 128×64)
- Potentiometer (10kΩ)
- 3 Push Buttons
- Jumper Wires
- Breadboard
- USB Cable

---

Wiring Summary

Stepper Motor Driver (ULN2003)

- IN1 → D8
- IN2 → D9
- IN3 → D10
- IN4 → D7
- VCC → 5V
- GND → GND

OLED Display (SPI)

- CS → D5
- DC → D6
- RESET → A1
- MOSI → D11
- SCK → D13
- VCC → 5V
- GND → GND

Potentiometer

- Signal → A0
- VCC → 5V
- GND → GND

Push Buttons

- Clockwise Button → D2
- Counter-Clockwise Button → D3
- Home Button → D4

---

Working

1. Rotate the potentiometer to select the target angle between 0° and 360°.
2. Press the CW button to rotate the motor by 45° clockwise.
3. Press the CCW button to rotate the motor by 45° counter-clockwise.
4. Press the HOME button to reset the current position to 0° (logical reset).
5. The OLED continuously displays:
   - Current Angle
   - Target Angle
   - Motor Direction
   - Current Step Count
6. The Serial Monitor prints motor movement and position updates.

---

Libraries Used

- SPI
- Adafruit GFX
- Adafruit SSD1306
- Stepper

---

Expected Output

- Potentiometer sets the target angle from 0° to 360°.
- Stepper motor rotates 45° for every CW or CCW button action.
- Home button resets the logical position to 0°.
- OLED displays the current angle, target angle, direction, and step count.
- Serial Monitor shows movement logs and updated position values.

---

How to Run

1. Open the project in Arduino IDE.
2. Install the required libraries:
   - Adafruit GFX
   - Adafruit SSD1306
3. Connect all components according to the wiring diagram.
4. Upload the code to the Arduino Uno.
5. Open the Serial Monitor at 115200 baud.
6. Operate the potentiometer and buttons to test the system.

7. Google Drive Link
8. https://drive.google.com/file/d/18yB702GCOT0TgCgu4dzRbn76K4e_KV5N/view?usp=drivesdk


