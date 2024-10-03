#define BLYNK_TEMPLATE_ID "TMPL659C2Lx8I"
#define BLYNK_TEMPLATE_NAME "7 segment"
#define BLYNK_AUTH_TOKEN "PShd9OZR4taMjLH3P72uem1V-Gm6AOTj"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "lab electronic";
char pass[] = "Labelec24!";

int a = D0;
int b = D1;
int c = D2;
int d = D3;
int e = D4;
int f = D5;

BlynkTimer waktu;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  waktu.setInterval(1000L, V0);
}

BLYNK_WRITE(V0){
  int slider = param.asInt();
  Serial.print(slider);
  if(slider==0){
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    Blynk.virtualWrite(V1, "Pagar Terbuka");
  }else if(slider==1){
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    Blynk.virtualWrite(V1, "Pagar Terbuka");
  }else if(slider==2){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    Blynk.virtualWrite(V1, "Pagar Terbuka");
  }else if(slider==3){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    Blynk.virtualWrite(V1, "Pagar Terbuka");
  }else if(slider==4){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    Blynk.virtualWrite(V1, "Pagar Terbuka");
  }else if(slider==5){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    Blynk.virtualWrite(V1, "Pagar Terbuka");
  }else if(slider==6){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    Blynk.virtualWrite(V1, "Pagar Tertutup");
  }
}

void loop() {
  Blynk.run();
  waktu.run();
}
