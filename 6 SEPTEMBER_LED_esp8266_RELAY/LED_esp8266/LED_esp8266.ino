#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6FMazeh_4"
#define BLYNK_TEMPLATE_NAME "LATIHAN SHERIN"
#define BLYNK_AUTH_TOKEN "eEKWaUfhqs4U4ldHLV41gjvuHascRmE7"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "lab electronic";
char pass[] = "Labelec24!";

const int LED1 = D0;
const int LED2 = D1;
const int relay = D2;


void setup()
{
  // Debug console
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(relay,OUTPUT);
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

BLYNK_WRITE (V0){
  int statusLED1 = param.asInt();
  digitalWrite(LED1, statusLED1);
}
BLYNK_WRITE (V1){
  int statusLED2 = param.asInt();
  digitalWrite(LED2, statusLED2);
}
BLYNK_WRITE (V2){
  int statusRelay = param.asInt();
  digitalWrite(relay, statusRelay);
}

void loop()
{
  Blynk.run();
}

