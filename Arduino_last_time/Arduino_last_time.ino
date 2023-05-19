#include <SoftwareSerial.h>

#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

String stream;
String yurek;


const int PulseWire = A0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;

const int lm35 = A1;
int input_val = 0;
float celsius;

String dataArr[2];
PulseSensorPlayground pulseSensor;


void setup() {
  Serial.begin(115200);
//  master.begin(115200);
  pulseSensor.begin();


  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);

}

void loop() {
  bpm();
  Serial.println(yurek);
}

void bpm() {

  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    yurek = myBPM;
  }
}
