#define BLYNK_PRINT Serial


#define BLYNK_TEMPLATE_ID "TMPL6Ehj-JpIR"
#define BLYNK_TEMPLATE_NAME "KONTROL LAMPU"
#define BLYNK_AUTH_TOKEN "FTlKapwKLLbT92jw8NaGRKyDlJVO7YEw"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "lab electronic";
char pass[] = "Labelec24!";

const int led1 = D1;
const int led2 = D2;
const int relay = D0;
int statusled;
void setup()
{
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(relay,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
BLYNK_WRITE(V0){
  statusled = param.asInt();
  digitalWrite (led1, statusled);
}

BLYNK_WRITE(V1){
  statusled = param.asInt();
  digitalWrite (led2, statusled);
}

BLYNK_WRITE(V2){
  statusled = param.asInt();
  digitalWrite (relay, statusled);
}
void loop()
{
  Blynk.run();
}
