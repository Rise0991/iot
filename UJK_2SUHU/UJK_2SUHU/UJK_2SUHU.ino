
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6S_HR5aCV"
#define BLYNK_TEMPLATE_NAME "DHT"
#define BLYNK_AUTH_TOKEN "sp2mFStQSwf1ka2Nizj93OnifUSI4nOz"
#define DHTPIN D5
#define DHTTYPE DHT11
#define BUZZER_PIN D6

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <LCD_I2C.h>

char ssid[] = "lab electronic";
char pass[] = "Labelec24!";

#define DHTPIN D5
#define BUZZER_PIN D6
#define DHTTYPE DHT11

WidgetLED led1(V4);

LCD_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer waktu;

int setPoint, enable;

float humi, temp;


BLYNK_WRITE(V0) {
  setPoint = param.asInt();
  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(setPoint);
  lcd.print(" ");
}

BLYNK_WRITE(V1) {
  enable = param.asInt();
  if (enable == 1) {
    lcd.setCursor(5, 1);
    lcd.print("e:ON ");
  } else {
    lcd.setCursor(5, 1);
    lcd.print("e:OFF");
  }
}

void sendDataSensor() {
  humi = dht.readHumidity();
  temp = dht.readTemperature();

  Blynk.virtualWrite(V2, temp);
  Blynk.virtualWrite(V3, humi);

  lcd.setCursor(0, 0);
  lcd.print("t:");
  lcd.print(temp);
  Serial.print("Suhu: ");
  Serial.print(temp);
  Serial.println("°C");

  lcd.setCursor(9, 0);
  lcd.print("h:");
  lcd.print(humi);
  Serial.print("Suhu: ");
  Serial.print(humi);
  Serial.println("%");
  delay(1000);

  if (temp >= setPoint && enable == 1) {
    digitalWrite(BUZZER_PIN, HIGH);
    led1.on();
    lcd.setCursor(11, 1);
    lcd.print("b:ON ");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    led1.off();
    lcd.setCursor(11, 1);
    lcd.print("b:OFF");
  }
}

void setup() {
  // Debug console
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();

  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("IRSYADDDDD");
  lcd.setCursor(0, 1);
  lcd.print("Kelas IOT");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(2000);
  lcd.clear();
  digitalWrite(BUZZER_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  waktu.setInterval(100L, sendDataSensor);
}

void loop() {
  Blynk.run();
  waktu.run();
}
