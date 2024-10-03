
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6O9VnQV87"
#define BLYNK_TEMPLATE_NAME "PINTU"
#define BLYNK_AUTH_TOKEN "91WcWxom-CXJWb-2A0OQC7SclQPXAPiJ"
#define merah "#D3435C"
#define hijau "#23C48E"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RELAY1_PIN D0
#define RELAY2_PIN D1
#define PINTU1_PIN D5
#define PINTU2_PIN D6
#define JENDELA_PIN D7

char ssid[] = "lab electronic";
char pass[] = "Labelec24!";

bool relay1, relay2;

BlynkTimer timer;

BLYNK_WRITE(V0) {
  relay1 = param.asInt();
  digitalWrite(RELAY1_PIN, relay1);
}

BLYNK_WRITE(V1) {
  relay2 = param.asInt();
  digitalWrite(RELAY2_PIN, relay2);
}
  
void sendDataSensor() {

  if (digitalRead(PINTU1_PIN) == 1) {
    Blynk.virtualWrite(V2, "PINTU UTAMA TERTUTUP");
    Blynk.setProperty(V2, "color", merah); // merubah warna label

  } else {
    Blynk.virtualWrite(V2, "PINTU UTAMA TERBUKA");
    Blynk.setProperty(V2, "color", hijau); // merubah warna label
  }

  if (digitalRead(PINTU2_PIN) == 1) {
    Blynk.virtualWrite(V3, "PINTU BELAKANG TERTUTUP");
    Blynk.setProperty(V3, "color", merah); // merubah warna label

  } else {
    Blynk.virtualWrite(V3, "PINTU BELAKANG TERBUKA");
    Blynk.setProperty(V3, "color", hijau); // merubah warna label
  } 

  if (digitalRead(JENDELA_PIN) == 1) {
    Blynk.virtualWrite(V4, "JENDELA SAMPING TERTUTUP");
    Blynk.setProperty(V4, "color", merah); // merubah warna label

  } else {
    Blynk.virtualWrite(V4, "JENDELA SAMPING TERBUKA");
    Blynk.setProperty(V4, "color", hijau); // merubah warna label
  }
}

void setup() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(PINTU1_PIN, INPUT);
  pinMode(PINTU2_PIN, INPUT);
  pinMode(JENDELA_PIN, INPUT);

  Serial.begin(9600);
  timer.setInterval(100L, sendDataSensor);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
}
