#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define IR_SENSOR_PIN_1 2 // Pin for IR Sensor 1
#define IR_SENSOR_PIN_2 3 // Pin for IR Sensor 2
#define IR_SENSOR_PIN_3 4 // Pin for IR Sensor 3

SoftwareSerial mySerial(10, 11); // RX, TX

DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  player.begin(mySerial);

  // Initialize IR sensor pins
  pinMode(IR_SENSOR_PIN_1, INPUT);
  pinMode(IR_SENSOR_PIN_2, INPUT);
  pinMode(IR_SENSOR_PIN_3, INPUT);
}

void loop() {
  // Check if IR sensor 1 is triggered
  if (digitalRead(IR_SENSOR_PIN_1) == HIGH) {
    playMusic(1); // Play music associated with sensor 1
    delay(1000); // Delay to avoid multiple triggers
  }

  // Check if IR sensor 2 is triggered
  if (digitalRead(IR_SENSOR_PIN_2) == HIGH) {
    playMusic(2); // Play music associated with sensor 2
    delay(1000); // Delay to avoid multiple triggers
  }

  // Check if IR sensor 3 is triggered
  if (digitalRead(IR_SENSOR_PIN_3) == HIGH) {
    playMusic(3); // Play music associated with sensor 3
    delay(1000); // Delay to avoid multiple triggers
  }
}

void playMusic(int trackNumber) {
  switch (trackNumber) {
    case 1:
      player.playMp3Folder(1); // Play track 001 from the SD card
      break;
    case 2:
      player.playMp3Folder(2); // Play track 002 from the SD card
      break;
    case 3:
      player.playMp3Folder(3); // Play track 003 from the SD card
      break;
    default:
      // Do nothing
      break;
  }
}
