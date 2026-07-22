# 🌤️ Simple Arduino Weather Station

Welcome to this beginner-friendly Arduino weather station! This project measures the local temperature and barometric pressure, calculates the sea-level pressure based on your altitude, and predicts the weather trend (Rising/Clear or Falling/Rain). 

## 🧰 Components Used
* **Arduino Board** (Uno, Nano, or Mega)
* **BMP180 or BMP085** Barometric Pressure & Temperature Sensor
* **0.96" OLED Display** (SSD1306, I2C interface)
* **Potentiometer** (e.g., 10kΩ) - *used to set your local altitude*
* **2x LEDs** (1 Green, 1 Red)
* **2x Resistors** (220Ω or 330Ω for the LEDs)
* Breadboard & Jumper wires

## 🔌 Wiring Summary

**1. I2C Devices (BMP180 Sensor & OLED Display)**
Both of these modules use the I2C bus, which means they can share the same pins!
* **VCC** ➡️ 5V (or 3.3V, depending on your module's logic level)
* **GND** ➡️ GND
* **SCL** ➡️ A5 (on Arduino Uno/Nano)
* **SDA** ➡️ A4 (on Arduino Uno/Nano)

**2. Potentiometer (Altitude Dial)**
* **Left Pin** ➡️ 5V
* **Middle Pin** ➡️ Analog Pin **A0**
* **Right Pin** ➡️ GND

**3. Weather Indicator LEDs**
* **Green LED (Positive/Long leg)** ➡️ Digital Pin **8**
* **Red LED (Positive/Long leg)** ➡️ Digital Pin **9**
* *Connect the negative/short leg of both LEDs to GND through a resistor.*

---

## 🏔️ Why Does Altitude Matter?
Imagine we live at the bottom of an "ocean" of air. The closer you are to the beach (sea level), the more air is stacked on top of you, making the air pressure higher. If you climb up a mountain, there is less air above you, so the pressure drops significantly.

If we didn't account for altitude, a weather station in a high-altitude city like Denver would constantly read low pressure. The station would mistakenly think a massive hurricane is rolling in every single day!

## 🌊 The Sea-Level Pressure Formula
To fix this altitude problem, meteorologists convert all pressure readings to what they *would be* if the station was sitting exactly at sea level. This "levels the playing field" so weather stations all over the world can be compared fairly.

The standard formula to do this looks like this:
`Sea Level Pressure = Current Pressure / (1 - (Altitude / 44330)) ^ 5.255`

*Don't worry about the heavy math, though!* The Adafruit library handles this automatically for us. 
In our code, we use the potentiometer to dial in our local altitude (from 0 to 2000 meters). We simply pass this altitude to the sensor:

```cpp
seaLevel = sensor.readSealevelPressure(alt) / 100.0;
```
Now, we have a perfectly accurate, adjusted sea-level pressure! 

## 📈 Predicting the Weather
Once we have the adjusted sea-level pressure, our code watches how it changes over time to guess the weather:
* **Pressure is RISING (^):** The air is getting heavier and more dense, which usually pushes clouds away. Expect **CLEAR** weather! (Green LED turns on)
* **Pressure is FALLING (v):** The air is getting lighter, allowing clouds and storms to roll in. Expect **RAIN**! (Red LED turns on)
* **Pressure is STABLE (-):** No big changes are happening right now.

Wokwi Simulation:
https://wokwi.com/projects/470263569034580993
