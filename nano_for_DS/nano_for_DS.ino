#include <SoftwareSerial.h>
#include <Arduino.h>
#include "HX711.h"
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>


String stream;
String yurek;
String agram;

const int PulseWire = A0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 600;

const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

PulseSensorPlayground pulseSensor;
HX711 scale;

String dataArr[2];

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  pulseSensor.begin();

  scale.set_scale(393.254);
  scale.tare();

}

void loop() {
  bpm();
  dataArr[0] = yurek;

  agram1();
  dataArr[1] = agram;
  Serial.println(dataArr[0] + "+" + dataArr[1]);
}
void bpm() {

  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    yurek = myBPM;
  }
  delay(3000);
}

void agram1() {
  if (0 < scale.get_units() && scale.get_units() < 15) {
    agram = "0";
  };
  if (15 < scale.get_units() && scale.get_units() < 50) {
    agram = "1";
  };
  if (50 < scale.get_units() && scale.get_units() < 100) {
    agram = "2";
  };
  if (100 < scale.get_units() && scale.get_units() < 150) {
    agram = "3";
  };
  if (150 < scale.get_units() && scale.get_units() < 200) {
    agram = "4";
  };
  if (200 < scale.get_units() && scale.get_units() < 250) {
    agram = "5";
  };
  if (250 < scale.get_units() && scale.get_units() < 300) {
    agram = "6";
  };
  if (300 < scale.get_units() && scale.get_units() < 350) {
    agram = "7";
  };
  if (350 < scale.get_units() && scale.get_units() < 400) {
    agram = "8";
  };
  if (400 < scale.get_units() && scale.get_units() < 450) {
    agram = "9";
  };
  if (450 < scale.get_units() && scale.get_units() < 550) {
    agram = "10";
  };

  scale.power_down();             // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}
