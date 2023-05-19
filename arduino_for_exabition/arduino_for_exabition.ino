#include <SoftwareSerial.h>
//
//#include <Arduino.h>
//#include "HX711.h"

#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

#include <DHT.h>
#define DHTPIN A1
#define DHTTYPE DHT22

String stream;
//String agram;
String yurek;
//
//const int LOADCELL_DOUT_PIN = 12;
//const int LOADCELL_SCK_PIN = 13;
//const int led2 = 5;
//
int ThermistorPin = A1;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf, Tlc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int sensorValue = 0;  // variable to store the value coming from the sensor


const int PulseWire = A0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;

unsigned long previousMillis = 0;
unsigned long interval = 3000;
String dataArr[3];
//HX711 scale;
PulseSensorPlayground pulseSensor;
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);
  //  master.begin(115200);
//  pinMode(led2, OUTPUT);
//  digitalWrite(led2, LOW);


  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);

//  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pulseSensor.begin();
  dht.begin();

//
//
//  scale.set_scale(393.254);
//  scale.tare();
}

String temp;
String hum;
void loop() {
  dht1();
//  scalle();
  lm();
  bpm();
  
  dataArr[0] = hum;
  dataArr[1] = temp;
//  dataArr[2] = celsius;
  dataArr[2] = yurek;
//  dataArr[4] = agram;


  Serial.println(dataArr[0]);
  Serial.println(dataArr[1]);
  Serial.println(dataArr[2]);
//  Serial.println(dataArr[3]);
//  Serial.println(dataArr[4]);
}

void bpm() {

  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    yurek = myBPM;
  }

}

//void scalle() {
//  if (0 < scale.get_units() && scale.get_units() < 100) {
//    agram = "0";
//  };
//  if (100 < scale.get_units() && scale.get_units() < 200) {
//    agram = "1";
//  };
//  if (200 < scale.get_units() && scale.get_units() < 300) {
//    agram = "2";
//  };
//  if (300 < scale.get_units() && scale.get_units() < 400) {
//    agram = "3";
//  };
//  if (400 < scale.get_units() && scale.get_units() < 550) {
//    agram = "4";
//  };
//  delay(1000);
//}

void dht1() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    hum = dht.readHumidity();
    temp = dht.readTemperature();
  }
}
void lm() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tlc = (Tc * (-1));
  Tf = (Tlc * 9.0) / 5.0 + 32.0;
  delay(3000);
}
