const int gasPin = A0;
const int flamePin = 7;

const int buzzer = 9;
const int greenLED = 10;
const int yellowLED = 11;
const int redLED = 12;

const bool FLAME_ACTIVE_LOW = true;

unsigned long previousMillis = 0;
unsigned long previousPrint = 0;
bool buzzerState = false;

void setup() {
  Serial.begin(9600);

  pinMode(flamePin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(buzzer, OUTPUT);

  Serial.println("Gas & Fire Safety Alert System");
  Serial.println("Warm up MQ-2 for about 2 minutes...");
}

void loop() {

  int gasValue = analogRead(gasPin);
  int gasPercent = map(gasValue, 0, 1023, 0, 100);
  gasPercent = constrain(gasPercent, 0, 100);

  bool flameDetected;

  if (FLAME_ACTIVE_LOW)
    flameDetected = (digitalRead(flamePin) == LOW);
  else
    flameDetected = (digitalRead(flamePin) == HIGH);

  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  String status = "";

  if (gasPercent < 30 && !flameDetected) {

    status = "SAFE";

    digitalWrite(greenLED, HIGH);
    noTone(buzzer);
  }

  else if (gasPercent >= 30 && gasPercent <= 60 && !flameDetected) {

    status = "WARNING";

    digitalWrite(yellowLED, HIGH);

    if (millis() - previousMillis >= 500) {
      previousMillis = millis();
      buzzerState = !buzzerState;

      if (buzzerState)
        tone(buzzer, 1000);
      else
        noTone(buzzer);
    }
  }

  else if (gasPercent > 60 && !flameDetected) {

    status = "GAS DANGER";

    digitalWrite(redLED, HIGH);

    tone(buzzer, 1500);
  }

  else if (gasPercent <= 60 && flameDetected) {

    status = "FIRE DANGER";

    digitalWrite(redLED, HIGH);

    if (millis() - previousMillis >= 200) {
      previousMillis = millis();
      buzzerState = !buzzerState;

      if (buzzerState)
        tone(buzzer, 2000);
      else
        noTone(buzzer);
    }
  }

  else {

    status = "GAS + FIRE DANGER";

    digitalWrite(redLED, HIGH);

    if (millis() - previousMillis >= 200) {
      previousMillis = millis();

      buzzerState = !buzzerState;

      if (buzzerState)
        tone(buzzer, 1000);
      else
        tone(buzzer, 2000);
    }
  }

  if (millis() - previousPrint >= 1000) {

    previousPrint = millis();

    Serial.print("Gas Raw: ");
    Serial.print(gasValue);

    Serial.print(" | GAS: ");
    Serial.print(gasPercent);
    Serial.print("%");

    Serial.print(" | Flame Pin: ");
    Serial.print(digitalRead(flamePin));

    Serial.print(" | FLAME: ");
    Serial.print(flameDetected ? "DETECTED" : "NONE");

    Serial.print(" | STATUS: ");
    Serial.println(status);
  }
}
