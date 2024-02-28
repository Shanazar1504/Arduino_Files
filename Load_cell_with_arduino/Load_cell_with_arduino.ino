#include <Arduino.h>
#include "HX711.h"
#include <SoftwareSerial.h>
#include <RH_ASK.h>
#include <SPI.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

HX711 scale;
int k;

// Bluetooth module setup
SoftwareSerial bluetoothSerial(4, 5); // RX, TX


void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600); // Bluetooth module baud rate
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(199.558);
  scale.tare(); // reset the scale to 0

  if (!rf_driver.init())
    Serial.println("RF driver init failed");
}

void loop() {
  Serial.print("one reading: \t");
  Serial.println(scale.get_units());

  if (0 < scale.get_units() && scale.get_units() < 50) {
    k = 10;
    senddata();
  } else if (50 < scale.get_units() && scale.get_units() < 100) {
    k = 30;
  } else if (100 < scale.get_units() && scale.get_units() < 150) {
    k = 60;
  } else if (150 < scale.get_units() && scale.get_units() < 200) {
    k = 80;
  } else if (200 < scale.get_units() && scale.get_units() < 250) {
    k = 100;
  }

  // Send value of k over Bluetooth
    bluetoothSerial.print("G:");
    bluetoothSerial.println(k);
  delay(1000);
}

void senddata (){

    const char* message = "K is equal to 10!";
    rf_driver.send((uint8_t *)message, strlen(message));
    rf_driver.waitPacketSent();
 
}
