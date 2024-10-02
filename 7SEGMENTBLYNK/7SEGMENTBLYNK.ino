#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6mUMC6Jxr"
#define BLYNK_TEMPLATE_NAME "7 SEGMENT"
#define BLYNK_AUTH_TOKEN "MIbTFDh8DNcSAUloEjGMO4nE2k_ebw0y"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "lab electronic";
char pass[] = "Labelec24!";

int segmentPins[] = { D0, D1, D2, D3, D7, D8};  // a, b, c, d, e, f


int gatePosition = 0;

byte segmentPatterns[][6] = {
  { 0, 0, 0, 0, 0, 0 },  // 0
  { 0, 0, 0, 0, 0, 1 },  // 1
  { 0, 0, 0, 0, 1, 1 },  // 2
  { 0, 0, 0, 1, 1, 1 },  // 3
  { 0, 0, 1, 1, 1, 1 },  // 4
  { 0, 1, 1, 1, 1, 1 },  // 5
  { 1, 1, 1, 1, 1, 1 }   // 6

};

const char* gateStatus[] = { "Tertutup", "1/6 Terbuka", "2/6 Terbuka", "3/6 Terbuka", "4/6 Terbuka", "5/6 Terbuka", "Terbuka Semua" };

BLYNK_WRITE(V0) {
  gatePosition = param.asInt();
  updateSevenSegment();
  updateGateStatus();   
}
 
void updateSevenSegment() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], segmentPatterns[gatePosition][i]);
  }
}

void updateGateStatus() {
  Blynk.virtualWrite(V1, gateStatus[gatePosition]);
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  updateGateStatus();
}

void loop() {
  Blynk.run();
}