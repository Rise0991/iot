#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6y9dFhpaE"
#define BLYNK_TEMPLATE_NAME "sensor"
#define BLYNK_AUTH_TOKEN "d8f9_V2oPi16usmMXy2r-KdUcipdw3E9"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RELAY_PIN D0
#define RELAY_SW_PIN 1
#define MODE_SW_PIN D8
#define GREEN_LED_PIN D3
#define YELLOW_LED_PIN D4
#define RED_LED_PIN D7
#define ECHO_PIN D5
#define TRIG_PIN D6

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "lab electronic";
char pass[] = "Labelec24!";

BlynkTimer waktu;

WidgetLED led1(V1);

#define BLYNK_GREEN     "#23C48E"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"

float waterLevel, capacity;
bool mode, relayState, buttonState;
int setPoint;
int sensorHeight = 45; // cm
int tankHeight = 40; // cm

BLYNK_CONNECTED() {
  // Turn LED on, so colors are visible
  led1.on();
}

BLYNK_WRITE(V1){
  setPoint = param.asInt();
}

BLYNK_WRITE(V3){
  mode = param.asInt();
}

void sendData(){
  waterLevel = sensorHeight - distance();
  capacity = (waterLevel * 100) / tankHeight;

  Blynk.virtualWrite(V0, capacity);

  if (waterLevel < 10){
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    led1.setColor(BLYNK_RED);
  }
  else if(waterLevel < 25){
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    led1.setColor(BLYNK_YELLOW);
  }
  else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    led1.setColor(BLYNK_GREEN);
  }
    // Sync Physical Button untuk mode (AUTO - MANUAL)
    if (digitalRead(MODE_SW_PIN) == HIGH) {
    // btnState is used to avoid sequential toggles
    if (buttonState != HIGH) {

      // Toggle LED state
      mode = !mode;

      // Update Button Widget
      Blynk.virtualWrite(V3, mode);
    }
    buttonState = HIGH;
  } else {
    buttonState = LOW;
  }

  // Kondisi Relay berdasarkan kapasitas air
  //Mode Auto
  if (mode){
    if(capacity < setPoint){
      relayState = true;
    } else if (capacity >= 100) {
      relayState = false;
    }
    digitalWrite(RELAY_PIN, relayState);
  } 
  // Mode Manual
  else {
    if(digitalRead(RELAY_SW_PIN) == 0){   // pakai PushButton PullUp
      relayState = !relayState;
    }
    digitalWrite(RELAY_PIN, relayState);
  }

  // Menampilkan status pada Blynk Widget Label
  if (relayState) {
    Blynk.virtualWrite(V4, "POMPA HIDUP");
  }
  else {
    Blynk.virtualWrite(V4, "POMPA MATI");
  }
}

float distance(){
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration_us = pulseIn (ECHO_PIN, HIGH);
  float distance_cm = 0.017 * duration_us;
  return distance_cm;
  Serial.print("Jarak : ");
  Serial.println(distance_cm);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RELAY_SW_PIN, INPUT_PULLUP);
  pinMode(MODE_SW_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  waktu.setInterval(100L, sendData);
}

void loop()
{
  Blynk.run();
  waktu.run();
}
