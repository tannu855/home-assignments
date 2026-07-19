#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define SOIL_PIN 34
#define DHTPIN 4
#define DHTTYPE DHT22

#define RELAY_PIN 26
#define BUTTON_PIN 25

#define GREEN_LED 18
#define RED_LED 19
#define BUZZER 23

DHT dht(DHTPIN, DHTTYPE);

const int DRY_VALUE = 3200;
const int WET_VALUE = 1200;

bool pumpOn = false;

unsigned long previousMillis = 0;
const unsigned long interval = 300000;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  dht.begin();
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while (true);
  }
  display.clearDisplay();
  display.display();
  readSensors();
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) manualWater();
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    readSensors();
  }
}

void readSensors() {
  int raw = analogRead(SOIL_PIN);
  int moisture = map(raw, DRY_VALUE, WET_VALUE, 0, 100);
  moisture = constrain(moisture, 0, 100);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  String status;
  if (!pumpOn && moisture < 30) pumpOn = true;
  if (pumpOn && moisture > 40) pumpOn = false;
  digitalWrite(RELAY_PIN, pumpOn ? LOW : HIGH);
  if (moisture < 30) {
    status = "DRY";
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    tone(BUZZER, 1000, 300);
  } else if (moisture <= 70) {
    status = "OPTIMAL";
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  } else {
    status = "WET";
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
  Serial.print("Raw: "); Serial.print(raw);
  Serial.print("  Moisture: "); Serial.print(moisture); Serial.print("%");
  Serial.print("  Temp: "); Serial.print(temperature); Serial.print(" C");
  Serial.print("  Humidity: "); Serial.print(humidity); Serial.print("%");
  Serial.print("  Status: "); Serial.println(status);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Soil: "); display.print(moisture); display.println("%");
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Humidity: "); display.print(humidity); display.println("%");
  display.print("Status:"); display.println(status);
  display.drawRect(0,54,120,8,WHITE);
  int bar = map(moisture,0,100,0,118);
  display.fillRect(1,55,bar,6,WHITE);
  display.display();
}

void manualWater() {
  Serial.println("Manual Watering Started");
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(RED_LED, HIGH);
  tone(BUZZER, 1500);
  delay(5000);
  noTone(BUZZER);
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(RED_LED, LOW);
  Serial.println("Manual Watering Finished");
  readSensors();
}

