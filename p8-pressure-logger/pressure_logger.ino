#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

#define POT_PIN A0
#define GREEN_LED 8
#define RED_LED 9

unsigned long lastLogTime = 0;
unsigned long lastDisplayTime = 0;
const unsigned long LOG_INTERVAL = 30000;    
const unsigned long DISPLAY_INTERVAL = 5000; 

float pressureLog[24];
int logIndex = 0;
bool bufferFull = false;

bool showPage1 = true;
String currentTrend = "CALC...";
float currentTemp = 0;
float currentPressure_hPa = 0;
float seaLevelPressure_hPa = 0;
float localAltOffset = 0;

void setup() {
  Serial.begin(9600); 
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  if (!bmp.begin()) {
    Serial.println(F("BMP180/BMP085 not found! Check wiring."));
    while (1); 
  }
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(F("Weather Station"));
  display.println(F("Initializing..."));
  display.display();
  
  Serial.println(F("Time(s)\t| Temp(*C)\t| Alt(m)\t| Press(hPa)\t| Trend    \t| Diff(hPa)"));
  Serial.println(F("-----------------------------------------------------------------------------------"));

  delay(2000);
  logData(); 
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = currentMillis;
    logData();
  }

  if (currentMillis - lastDisplayTime >= DISPLAY_INTERVAL) {
    lastDisplayTime = currentMillis;
    showPage1 = !showPage1;
    updateDisplay();
  }
}

void logData() {
  int potValue = analogRead(POT_PIN);
  localAltOffset = (potValue / 1023.0) * 2000.0;

  sensors_event_t event;
  bmp.getEvent(&event);
  
  if (event.pressure) {
    currentPressure_hPa = event.pressure; 
    bmp.getTemperature(&currentTemp);
  }

  seaLevelPressure_hPa = bmp.seaLevelForAltitude(localAltOffset, currentPressure_hPa);

  pressureLog[logIndex] = seaLevelPressure_hPa;
  
  float oldestPressure;
  if (bufferFull) {
    oldestPressure = pressureLog[(logIndex + 1) % 24]; 
  } else {
    oldestPressure = pressureLog[0]; 
  }

  float pressureDiff = seaLevelPressure_hPa - oldestPressure;

  if (pressureDiff > 0.5) {
    currentTrend = "RISING ^";
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  } else if (pressureDiff < -0.5) {
    currentTrend = "FALLING v";
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  } else {
    currentTrend = "STABLE -";
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }

  Serial.print(millis() / 1000);
  Serial.print(F("\t| "));
  Serial.print(currentTemp, 2);
  Serial.print(F("\t\t| "));
  Serial.print(localAltOffset, 0);
  Serial.print(F("\t\t| "));
  Serial.print(seaLevelPressure_hPa, 2);
  Serial.print(F("\t| "));
  Serial.print(currentTrend);
  
  if (currentTrend.length() < 9) {
    Serial.print(F("\t| "));
  } else {
    Serial.print(F(" \t| "));
  }
  
  Serial.println(pressureDiff, 2);

  logIndex++;
  if (logIndex >= 24) {
    logIndex = 0;
    bufferFull = true;
  }
}

void updateDisplay() {
  display.clearDisplay();
  
  if (showPage1) {
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print(currentTemp, 1);
    display.println(F(" C"));
    
    display.setTextSize(1);
    display.setCursor(0, 25);
    display.print(F("SL Press: "));
    display.print(seaLevelPressure_hPa, 1); 
    display.println(F(" hPa"));
    
    display.setCursor(0, 40);
    display.print(F("Alt Set: "));
    display.print(localAltOffset, 0);
    display.println(F(" m"));
  } else {
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println(F("WEATHER TREND:"));
    
    display.setCursor(0, 20);
    display.setTextSize(2);
    display.println(currentTrend);
    
    display.setCursor(0, 45);
    display.setTextSize(1);
    if (currentTrend.indexOf("RISING") >= 0) {
      display.println(F("Predict: CLEAR"));
    } else if (currentTrend.indexOf("FALLING") >= 0) {
      display.println(F("Predict: RAIN"));
    } else {
      display.println(F("Predict: NO CHANGE"));
    }
  }
  
  display.display();
}
