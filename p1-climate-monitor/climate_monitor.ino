#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define RED_LED 8
#define GREEN_LED 9
#define BUZZER 10

unsigned long sensorTimer = 0;
unsigned long csvTimer = 0;
unsigned long screenTimer = 0;
unsigned long buzzerTimer = 0;

bool buzzerOn = false;
bool dangerState = false;

float temp = 0;
float hum = 0;

float maxTemp = -100;
float minTemp = 100;

int screen = 0;

String statusText = "COMFORT";

void setup() {

  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12,20);
  display.println("CLIMATE");
  display.display();

  delay(2000);

  Serial.println("Time(ms),Temp,Humidity,Status");
}

void loop() {

  unsigned long now = millis();

  if (buzzerOn && now - buzzerTimer >= 1000) {
    noTone(BUZZER);
    buzzerOn = false;
  }

  if (now - sensorTimer >= 2000) {

    sensorTimer = now;

    temp = dht.readTemperature();
    hum = dht.readHumidity();

    if (!isnan(temp) && !isnan(hum)) {

      if (temp > maxTemp) maxTemp = temp;
      if (temp < minTemp) minTemp = temp;

      bool danger = (temp > 38 || hum > 80);

      if (danger) {

        statusText = "DANGER";

        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);

        if (!dangerState) {
          tone(BUZZER, 1000);
          buzzerOn = true;
          buzzerTimer = now;
        }

        dangerState = true;

      } else {

        dangerState = false;

        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);

        if (temp < 22)
          statusText = "COOL";
        else if (temp <= 30 && hum <= 60)
          statusText = "COMFORT";
        else
          statusText = "HOT";
      }

      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print(" C   Humidity: ");
      Serial.print(hum);
      Serial.print("%   Status: ");
      Serial.println(statusText);
    }
  }
  if (now - csvTimer >= 5000) {
    csvTimer = now;

    Serial.print(now);
    Serial.print(",");
    Serial.print(temp, 1);
    Serial.print(",");
    Serial.print(hum, 1);
    Serial.print(",");
    Serial.println(statusText);
  }

  if (now - screenTimer >= 5000) {
    screenTimer = now;
    screen++;
    if (screen > 2) screen = 0;
  }

  display.clearDisplay();

  switch (screen) {

    case 0:

      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("T:");
      display.print(temp, 1);
      display.println("C");

      display.setCursor(0, 32);
      display.print("H:");
      display.print(hum, 1);
      display.println("%");
      break;

    case 1:

      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("STATUS");

      display.setCursor(0, 30);
      display.println(statusText);

      display.setTextSize(1);
      display.setCursor(0, 56);
      display.print(temp, 1);
      display.print("C  ");
      display.print(hum, 1);
      display.print("%");
      break;

    case 2:

      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("MAX / MIN TEMP");

      display.drawLine(0, 10, 127, 10, WHITE);

      display.setTextSize(2);

      display.setCursor(0, 18);
      display.print("MX:");
      display.print(maxTemp, 1);

      display.setCursor(0, 42);
      display.print("MN:");
      display.print(minTemp, 1);

      break;
  }

  display.display();
}
