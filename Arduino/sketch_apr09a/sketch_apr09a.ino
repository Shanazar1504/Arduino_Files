#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <SoftwareSerial.h>
char inchar;
SoftwareSerial blue(0, 1 );
String Sms;
String humidity = "Cyglylyk: %";
String temperature = "Temperature:  ";
String sign = " *C";
int t;
int h;
void setup() {
  Serial.begin(9600);
  blue.begin(9600);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  pinMode(9, OUTPUT);

}

void loop() {
  if (blue.available() == 0);
  if (blue.available() > 0) {
    inchar = blue.read();
    //Serial.println(inchar);
    //delay(20);
    if (inchar == 'v') {
      //delay(10);
      //Serial.println(inchar);
      //delay(1000);
      int h = dht.readHumidity();
      int t = dht.readTemperature();
      Sms = Sms + "Cyglylyk: ";
      Sms.concat(h);
      Sms = Sms + "%      Temperature: ";
      Sms.concat(t);
      Sms = Sms + "*C";
      blue.print(Sms);
      Serial.println(Sms);
      delay(1000);
      Sms = " ";
      if (isnan(h) || isnan(t)) {
        Serial.println("Nadogry!!!");
        return;
      }
    }
  }
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if (t > 40) {
    digitalWrite(9, 1);
  }
  if (t < 40) {
    digitalWrite(9, 0);
  }
  lcd.setCursor(0, 0);
  lcd.print("Cyglylyk: ");
  lcd.print(h);
  lcd.print("% ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223); //degree symbol
  lcd.print("C ");
}
