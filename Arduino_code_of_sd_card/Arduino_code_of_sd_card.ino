#include <Wire.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define SD_ChipSelectPin 4

TMRpcm saz;

int state = 0;
int prev = 0;

void setup() {
  saz.speakerPin = 9;
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  saz.setVolume(5);
  saz.play("1.wav");

}

void loop() {
  if (state >= 0) {
    music1();
    music2();
    music3();
    music4();
    music5();
  }
  delay(1);
  prev = state;
}
void music1() {
  state = 1;
  if (prev != state) {
    saz.setVolume(5);
    saz.play("1.wav");
    delay(25000);
  }
}
void music2() {
  state = 2;
  if (prev != state) {
    saz.setVolume(5);
    saz.play("2.wav");
    delay(25000);
  }
}
void music3() {
  state = 3;
  if (prev != state) {
    saz.setVolume(5);
    saz.play("3.wav");
    delay(25000);
  }
}
void music4() {
  state = 4;
  if (prev != state) {
    saz.setVolume(5);
    saz.play("4.wav");
    delay(25000);
  }
}
void music5() {
  state = 5;
  if (prev != state) {
    saz.setVolume(5);
    saz.play("5.wav");
    delay(25000);
  }
}
