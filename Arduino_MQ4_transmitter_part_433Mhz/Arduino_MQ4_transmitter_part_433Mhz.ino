#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

const int transmitPin = 12;   // Define the pin connected to the RF transmitter module
const uint8_t definedDeviceKeyGas = 102; // Define device key for gas detector data
const int gasSensorPin = 4;   // Digital pin connected to the gas sensor

struct SensorDataGas {
  uint8_t deviceKey;
  int gasValue;
};

void setup() {
  Serial.begin(9600);         // Initialize serial communication for debugging
  if (!rf_driver.init())
    Serial.println("RF driver init failed");

  pinMode(transmitPin, OUTPUT); // Set the data pin as output
  pinMode(gasSensorPin, INPUT); // Set the gas sensor pin as input
}

void loop() {
  int gasValue = digitalRead(gasSensorPin); // Read gas sensor digital output
  gasValue = (gasValue == HIGH) ? 1 : 0; // Convert gas value to binary (0 or 1)

  // Construct data packet
  SensorDataGas dataPacket;
  dataPacket.deviceKey = definedDeviceKeyGas;
  dataPacket.gasValue = gasValue;

  // Send the data packet
  rf_driver.send((uint8_t*)&dataPacket, sizeof(dataPacket));
  rf_driver.waitPacketSent();
  
  delay(500); // Delay before sending the next message
}
