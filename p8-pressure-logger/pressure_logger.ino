#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 screen(128, 64, &Wire, -1);
Adafruit_BMP085 sensor;

int potPin = A0;
int greenLed = 8;
int redLed = 9;

float history[6];
String trend = "CALC...";
float temp = 0;
float seaLevel = 0;
float alt = 0;

int loopCount = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  
  sensor.begin();
  screen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  screen.clearDisplay();
  screen.setTextColor(WHITE);
  screen.setTextSize(1);
  screen.setCursor(0, 20);
  screen.println("Weather Station");
  screen.println("Starting up...");
  screen.display();
  delay(2000);

  for (int i = 0; i < 6; i++) {
    history[i] = 0;
  }
}

void loop() {
  if (loopCount == 0) {
    checkWeather();
  }

  showScreen1();
  delay(5000);

  showScreen2();
  delay(5000);

  loopCount++;
  if (loopCount >= 3) {
    loopCount = 0;
  }
}

void checkWeather() {
  int pot = analogRead(potPin);
  alt = (pot / 1023.0) * 2000.0;
  
  temp = sensor.readTemperature();
  float pressure = sensor.readPressure();
  seaLevel = sensor.readSealevelPressure(alt) / 100.0;
  
  for (int i = 0; i < 5; i++) {
    history[i] = history[i + 1];
  }
  history[5] = seaLevel;
  
  if (history[0] != 0) {
    float diff = history[5] - history[0];
    
    if (diff > 0.5) {
      trend = "RISING ^";
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
    } else if (diff < -0.5) {
      trend = "FALLING v";
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
    } else {
      trend = "STABLE -";
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
    }
  }
}

void showScreen1() {
  screen.clearDisplay();
  screen.setCursor(0, 0);
  screen.setTextSize(2);
  screen.print(temp, 1);
  screen.println(" C");
  
  screen.setTextSize(1);
  screen.setCursor(0, 25);
  screen.print("SL Press: ");
  screen.print(seaLevel, 1); 
  screen.println(" hPa");
  
  screen.setCursor(0, 40);
  screen.print("Alt Set: ");
  screen.print(alt, 0);
  screen.println(" m");
  screen.display();
}

void showScreen2() {
  screen.clearDisplay();
  screen.setCursor(0, 0);
  screen.setTextSize(1);
  screen.println("WEATHER TREND:");
  
  screen.setCursor(0, 20);
  screen.setTextSize(2);
  screen.println(trend);
  
  screen.setCursor(0, 45);
  screen.setTextSize(1);
  if (trend == "RISING ^") {
    screen.println("Predict: CLEAR");
  } else if (trend == "FALLING v") {
    screen.println("Predict: RAIN");
  } else {
    screen.println("Predict: NO CHANGE");
  }
  screen.display();
}
