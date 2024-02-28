#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

const int transmitPin = 12; // Define the pin connected to the RF transmitter module
const uint8_t deviceKey = 103; // Define the device key
const int fireSensorPin = 2; // Analog pin connected to the fire sensor

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  if (!rf_driver.init())
    Serial.println("RF driver init failed");

  pinMode(transmitPin, OUTPUT); // Set the data pin as output
}

void loop() {
  int fireValue = digitalRead(fireSensorPin); // Read fire sensor analog output as integer
  
  // Print fire value to Serial Monitor
  Serial.print("Fire Value: ");
  Serial.println(fireValue);

  uint8_t data[sizeof(deviceKey) + sizeof(fireValue)]; // Byte array to hold the device key and fire value

  // Copy the device key into the byte array
  memcpy(data, &deviceKey, sizeof(deviceKey));

  // Copy the fire value into the byte array after the device key
  memcpy(data + sizeof(deviceKey), &fireValue, sizeof(fireValue));

  // Send the byte array
  rf_driver.send(data, sizeof(data));
  rf_driver.waitPacketSent();
  
  delay(500); // Delay before sending the next message
}
