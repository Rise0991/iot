
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6S1GKqYIf"
#define BLYNK_TEMPLATE_NAME "TUGAS11"
#define BLYNK_AUTH_TOKEN "DtW2ZWqs2NkTDvXz2kXnRqUhHNK6gzUW"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "AndroidAP8AAF";
char pass[] = "embuleneng";

BlynkTimer timer;

const int Relay1 = D0;
const int Relay2 = D1;
const int TS0 = D5;
const int TS1 = D6;

int toggle0, toggle1, relay1, relay2;

void setup()
{
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(TS0, INPUT);
  pinMode(TS1, INPUT);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(100L, utama);
}

BLYNK_WRITE (V0){
  relay1 = param.asInt();
  
}
BLYNK_WRITE (V1){
  relay2 = param.asInt();
}

void utama (){
  toggle0 = digitalRead(TS0);
  toggle1 = digitalRead(TS1);
  

  if(toggle0 == 1 || relay1 == 1){
    Blynk.virtualWrite(V2, "PINTU UTAMA TERBUKA");
    Blynk.virtualWrite(V4, HIGH);
    Blynk.virtualWrite(V0, HIGH);
    digitalWrite(Relay1, HIGH);
  }
  else{
    Blynk.virtualWrite(V2, "PINTU UTAMA TERTUTUP");
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V0, LOW);
    digitalWrite(Relay1, LOW);
  }
  if(toggle1 == 1 || relay2 == 1){
    Blynk.virtualWrite(V3, "PINTU UTAMA TERBUKA");
    Blynk.virtualWrite(V4, HIGH);
    Blynk.virtualWrite(V1, HIGH);
    digitalWrite(Relay2, HIGH);
  }
  else{
    Blynk.virtualWrite(V3, "PINTU UTAMA TERTUTUP");
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V1, LOW);
    digitalWrite(Relay2, LOW);
  }
}



void loop(){
  timer.run();
  Blynk.run();
}

