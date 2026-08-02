#include <WiFi.h>
#include <esp_now.h>
#include <Keypad.h>
#include "mbedtls/aes.h"

byte key[16] = {
  0x10,0x22,0x34,0x46,
  0x58,0x6A,0x7C,0x8E,
  0x91,0xA2,0xB3,0xC4,
  0xD5,0xE6,0xF7,0x08
};

mbedtls_aes_context aes;

uint8_t receiverMAC[] = {
  0x88,0xF1,0x55,
  0x32,0x5C,0xE4
};

typedef struct
{
  byte aes[16];

} Packet;


Packet dataPkt;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] =
{
  13,12,14,27
};


byte colPins[COLS] =
{
  26,25,33,32
};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);


String passTxt = "";
esp_now_peer_info_t peerInfo;

void onSent(
const wifi_tx_info_t *info,
esp_now_send_status_t status
)
{
  Serial.print("Send Status : ");

  if(status == ESP_NOW_SEND_SUCCESS)
    Serial.println("SUCCESS");

  else
    Serial.println("FAILED");
}

void setup()
{

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("Sender MAC: ");
  Serial.println(WiFi.macAddress());  
  mbedtls_aes_init(&aes);

  mbedtls_aes_setkey_enc(
    &aes,
    key,
    128
  );
  
  if(esp_now_init()!=ESP_OK)
  {
    Serial.println("ESP-NOW Failed");
    return;
  }

  esp_now_register_send_cb(onSent);
  memcpy(
    peerInfo.peer_addr,
    receiverMAC,
    6
  );

  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if(esp_now_add_peer(&peerInfo)!=ESP_OK)
  {
    Serial.println("Peer Add Failed");
    return;
  }

  Serial.println("AES Sender Ready");
  Serial.println("Enter 4 digit PIN");
  Serial.println("* = Clear   # = Submit");

}

void loop()
{
  char key = keypad.getKey();
  if(!key)
    return;

  if(key=='*')
  {
    passTxt="";
    Serial.println("\nPassword Cleared");
    return;
  }

  if(key=='#')
  {

    if(passTxt.length()!=4)
    {
      Serial.println("\nEnter exactly 4 digits");
      return;
    }
    byte plain[16];

    memset(
      plain,
      0,
      16
    );

    for(int i=0;i<4;i++)
    {
      plain[i]=passTxt[i];
    }

    for(int i=4;i<16;i++)
    {
      plain[i]=random(0,255);
    }

    mbedtls_aes_crypt_ecb(
      &aes,
      MBEDTLS_AES_ENCRYPT,
      plain,
      dataPkt.aes
    );

    esp_err_t result =
    esp_now_send(
      receiverMAC,
      (uint8_t*)&dataPkt,
      sizeof(dataPkt)
    );

    if(result==ESP_OK)
      Serial.println("\nEncrypted PIN Sent");

    else
      Serial.println("\nSend Failed");

    passTxt="";
    return;
  }

  if(key>='0' && key<='9')
  {

    if(passTxt.length()<
      passTxt += key;
      Serial.print("*");
    }

  }

}
