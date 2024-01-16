#include <SPI.h>

#define DS_PIN D1
#define SHCP_PIN D2
#define STCP_PIN D3

byte stateData = 0;

void setup() {
  pinMode(DS_PIN, OUTPUT);
  pinMode(SHCP_PIN, OUTPUT);
  pinMode(STCP_PIN, OUTPUT);

  // Set all outputs to LOW initially
  digitalWrite(STCP_PIN, LOW);
  shiftOut(DS_PIN, SHCP_PIN, MSBFIRST, 0x00);  // Send 0x00 to clear all outputs
  digitalWrite(STCP_PIN, HIGH);
}

void loop() {
  // Sequentially turn on and off each relay
  for (int channel = 0; channel < 8; channel++) {
    setRelay(channel, HIGH);  // Turn on relay
    delay(1000);
    setRelay(channel, LOW);   // Turn off relay
    delay(1000);
  }
}

void setRelay(int channel, int state) {
  // Set the state of a specific relay channel
  bitWrite(stateData, channel, state);
  
  // Shift the data out to the shift register
  digitalWrite(STCP_PIN, LOW);
  shiftOut(DS_PIN, SHCP_PIN, MSBFIRST, stateData);
  digitalWrite(STCP_PIN, HIGH);
}
