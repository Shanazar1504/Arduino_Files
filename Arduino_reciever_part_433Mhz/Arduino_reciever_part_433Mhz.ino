#include <RH_ASK.h>
#include <SPI.h>
#include <SoftwareSerial.h>

RH_ASK rf_driver;

SoftwareSerial master(4, 5); // RX, TX

const int receivePin = 11; // Pin connected to RF receiver module
const int buzzer = 7;

const uint8_t definedDeviceKeyTempHumid = 101; // Define device key for temperature and humidity data
const uint8_t definedDeviceKeyGas = 102; // Define device key for gas detector data
const uint8_t definedDeviceKeyFire = 103; // Define device key for fire sensor data

struct SensorDataTempHumid {
  uint8_t deviceKey;
  float humidity;
  float temperature;
};

struct SensorDataGas {
  uint8_t deviceKey;
  int gasValue; // Change data type to int for gas value
};

struct SensorDataFire {
  uint8_t deviceKey;
  int fireValue; // Assuming fire value is an integer representing intensity or presence
};

void setup() {
  Serial.begin(9600); // Initialize Serial communication for debugging
  master.begin(115200);
  if (!rf_driver.init())
    Serial.println("RF driver init failed");

  pinMode(receivePin, INPUT); // Set the pin as input for RF receiver module
  pinMode(buzzer, OUTPUT); // Set the pin as input for RF receiver module
}

void loop() {
  uint8_t buf[32]; // Buffer to store received data
  uint8_t buflen = sizeof(buf); // Maximum message length

  if (rf_driver.recv(buf, &buflen)) { // Check if data is received
    if (buflen >= sizeof(uint8_t)) { // Ensure there is at least one byte received
      uint8_t deviceKey = buf[0]; // Extract device key from received data
      if (deviceKey == definedDeviceKeyTempHumid && buflen == sizeof(SensorDataTempHumid)) { // Check if received data is temperature and humidity
        SensorDataTempHumid receivedDataTH;
        memcpy(&receivedDataTH, buf, sizeof(receivedDataTH));
        Serial.print("Device Key: ");
        Serial.print(receivedDataTH.deviceKey);
        master.println(receivedDataTH.deviceKey);
        Serial.print(", Temperature: ");
        Serial.print(receivedDataTH.temperature);
        master.println(receivedDataTH.temperature);
        Serial.print(" C, Humidity: ");
        Serial.print(receivedDataTH.humidity);
        master.println(receivedDataTH.humidity);
        Serial.println(" %");
      } else if (deviceKey == definedDeviceKeyGas && buflen == sizeof(SensorDataGas)) { // Check if received data is gas detector value
        SensorDataGas receivedDataGas;
        memcpy(&receivedDataGas, buf, sizeof(receivedDataGas));
        Serial.print("Device Key: ");
        Serial.print(receivedDataGas.deviceKey);
        master.println(receivedDataGas.deviceKey);
        Serial.print(", Gas Value: ");
        Serial.print(receivedDataGas.gasValue);
        master.println(receivedDataGas.gasValue);
        Serial.println(" ppm");
        if (receivedDataGas.gasValue == 0) {
          soundBuzzer();
        }
        else {
          digitalWrite(buzzer, LOW);
        }
      } else if (deviceKey == definedDeviceKeyFire && buflen == sizeof(SensorDataFire)) { // Check if received data is fire sensor value
        SensorDataFire receivedDataFire;
        memcpy(&receivedDataFire, buf, sizeof(receivedDataFire));
        Serial.print("Device Key: ");
        Serial.print(receivedDataFire.deviceKey);
        master.println(receivedDataFire.deviceKey);
        Serial.print(", Fire Value: ");
        Serial.print(receivedDataFire.fireValue);
        master.println(receivedDataFire.fireValue);
        Serial.println(" intensity");
        if (receivedDataFire.fireValue == 0) {
          soundBuzzer();
        }
        else {
          digitalWrite(buzzer, LOW);
        }
      } else {
        Serial.println("Received data format mismatch");
      }
    } else {
      Serial.println("Received data length too short");
    }
  }
}

// Function to sound the buzzer
void soundBuzzer() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
}
