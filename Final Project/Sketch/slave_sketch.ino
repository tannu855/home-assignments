#include <WiFi.h>
#include <esp_now.h>
#include "mbedtls/cipher.h"
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

byte key[16] = {

  0x10,0x22,0x34,0x46,
  0x58,0x6A,0x7C,0x8E,
  0x91,0xA2,0xB3,0xC4,
  0xD5,0xE6,0xF7,0x08

};


mbedtls_cipher_context cipher;

#define greenLed 18
#define redLed   19
#define buzzer    23
#define servoPin 5

LiquidCrystal_I2C screen(0x27,16,2);
Servo lockerServo;

typedef struct
{
  byte cipher[16];

} Packet;

Packet packet;

void onRecv(
const esp_now_recv_info *info,
const uint8_t *dataIn,
int len
)
{

  if(len != sizeof(Packet))
  {
    Serial.println("Wrong Packet");
    return;
  }



  memcpy(
    &packet,
    dataIn,
    sizeof(packet)
  );



  byte plain[16];

  mbedtls_cipher_crypt_ecb(
    &cipher,
    MBEDTLS_AES_DECRYPT,
    packet.cipher,
    plain
  );

  char receivedPassword[5];


  for(int i=0;i<4;i++)
  {
    receivedPassword[i]=plain[i];
  }


  receivedPassword[4]='\0';
  Serial.print("Received PIN: ");
  Serial.println(receivedPassword);

  char correctPassword[]="1111";

  if(strcmp(receivedPassword,correctPassword)==0)

  {

    Serial.println("ACCESS GRANTED");



    screen.clear();

    screen.setCursor(0,0);
    screen.print("ACCESS GRANTED");

    screen.setCursor(0,1);
    screen.print("Locker Opening");



    digitalWrite(greenLed,HIGH);
    lockerServo.write(90);

    digitalWrite(buzzer,HIGH);
    delay(300);
    digitalWrite(buzzer,LOW);
    delay(5000);
    lockerServo.write(0);
    digitalWrite(greenLed,LOW);
    screen.clear();
    screen.print("Locker Locked");

    delay(1500);

  }

  else

  {

    Serial.println("ACCESS DENIED");
    screen.clear();
    screen.setCursor(0,0);
    screen.print("ACCESS DENIED");
    screen.setCursor(0,1);
    screen.print("Wrong Password");
    digitalWrite(redLed,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(3000);
    digitalWrite(buzzer,LOW);
    digitalWrite(redLed,LOW);
    delay(1500);
    screen.clear();
    screen.print("Enter Password");
  }

}


void setup()

{

  Serial.begin(115200);
  pinMode(greenLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(greenLed,LOW);
  digitalWrite(redLed,LOW);
  digitalWrite(buzzer,LOW); 
  screen.init();
  screen.backlight();
  screen.clear();
  screen.setCursor(0,0);
  screen.print("SMART LOCKER");
  screen.setCursor(0,1);
  screen.print("Starting...");
  lockerServo.attach(servoPin);
  lockerServo.write(0);
  WiFi.mode(WIFI_STA);
  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress());
  mbedtls_cipher_init(&cipher);
  mbedtls_cipher_setkey_dec(
    &cipher,
    key,
    128
  );

  if(esp_now_init()!=ESP_OK)
  {
    Serial.println("ESP-NOW Failed");
    return;
  }

  esp_now_register_recv_cb(onRecv);
  delay(1500);
  screen.clear();
  screen.print("Enter Password");
  Serial.println("AES RECEIVER READY");

}

void loop()
{

}
