#include <SoftwareSerial.h>

#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>


String stream;
String yurek;
String body;

const int PulseWire = A0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 600;

int ThermistorPin = A1;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf, Tlc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int sensorValue = 0;  // variable to store the value coming from the sensor


PulseSensorPlayground pulseSensor;

String dataArr[2];

void setup() {
  Serial.begin(115200);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  pulseSensor.begin();
}

void loop() {
  dallas();
  dataArr[0] = Tlc;

  bpm();
  dataArr[1] = yurek;
  Serial.println(dataArr[0] + "+" + dataArr[1]);
}

void dallas() {
  // read the value from the sensor:
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tlc = (Tc * (-1));
  Tf = (Tlc * 9.0) / 5.0 + 32.0;
//  Serial.print(Tlc);
//  Serial.println(" C");
  delay(3000);
}

void bpm() {

  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    yurek = myBPM;
  }
  delay(3000);
}
