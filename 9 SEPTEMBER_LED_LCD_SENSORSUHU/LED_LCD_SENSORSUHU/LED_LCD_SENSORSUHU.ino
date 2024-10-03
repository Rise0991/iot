#define BLYNK_TEMPLATE_ID "TMPL6y9dFhpaE"
#define BLYNK_TEMPLATE_NAME "sensor"
#define BLYNK_AUTH_TOKEN "d8f9_V2oPi16usmMXy2r-KdUcipdw3E9"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Wire.h>
#include <LCD_I2C.h>

#define DHTPIN D5
#define DHTTYPE DHT11

BlynkTimer timer;

LCD_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

float h, t, setPoint = 0;
bool ledState = false;
bool systemEnabled = false; 
char ssid[] = "lab electronic";
char pass[] = "Labelec24!";
const int led = D0;  

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight(); 
  pinMode(led, OUTPUT);
  timer.setInterval(2000L, readSensors);
  dht.begin();  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

BLYNK_WRITE(V2) {
  setPoint = param.asFloat();
  Serial.print("Set Point baru: ");
  Serial.println(setPoint);
  Blynk.virtualWrite(V2, setPoint); 
}
BLYNK_WRITE(V3) {
  systemEnabled = param.asInt(); 
  Serial.print("System Enabled: ");
  Serial.println(systemEnabled);
  Blynk.virtualWrite(V3, systemEnabled ? 1 : 0);
}

void readSensors() {
  t = dht.readTemperature();
  h = dht.readHumidity();

  Blynk.virtualWrite(V0, t); 
  Blynk.virtualWrite(V1, h); 

  if (systemEnabled) {
    if (t > setPoint) {
      digitalWrite(led, HIGH);  
      ledState = true;
    } else {
      digitalWrite(led, LOW);  
      ledState = false;
    }
  } else {
    digitalWrite(led, LOW);
    ledState = false;
  }

  Blynk.virtualWrite(V4, ledState ? 1 : 0); 

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("% ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:"); 
  lcd.print(t);
  lcd.print("  H:"); 
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print((int)setPoint); 
  lcd.setCursor(5, 1);
  lcd.print("E:"); 
  lcd.print(systemEnabled ? "ON" : "OFF");
  lcd.setCursor(11, 1);
  lcd.print("L:"); 
  lcd.print(ledState ? "ON" : "OFF");
}

void loop() {
  Blynk.run();
  timer.run();
}