#include <RH_ASK.h>
#include <SPI.h>
#include <SoftwareSerial.h>

RH_ASK rf_driver;

SoftwareSerial bluetoothSerial(2, 3); // RX, TX for Bluetooth module

const int receivePin = 11; // Pin connected to RF receiver module
const int buzzer = 7;

const uint8_t definedDeviceKeyTempHumid = 101; // Define device key for temperature and humidity data
const uint8_t definedDeviceKeyGas = 102;       // Define device key for gas detector data
const uint8_t definedDeviceKeyFire = 103;      // Define device key for fire sensor data

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
  bluetoothSerial.begin(9600); // Initialize Bluetooth serial communication
  if (!rf_driver.init())
    Serial.println("RF driver init failed");

  pinMode(receivePin, INPUT); // Set the pin as input for RF receiver module
  pinMode(buzzer, OUTPUT);    // Set the pin as output for RF receiver module
}

void loop() {
  uint8_t buf[32];            // Buffer to store received data
  uint8_t buflen = sizeof(buf); // Maximum message length

  if (rf_driver.recv(buf, &buflen)) { // Check if data is received
    if (buflen >= sizeof(uint8_t)) {  // Ensure there is at least one byte received
      uint8_t deviceKey = buf[0];     // Extract device key from received data
      if (deviceKey == definedDeviceKeyTempHumid && buflen == sizeof(SensorDataTempHumid)) { // Check if received data is temperature and humidity
        SensorDataTempHumid receivedDataTH;
        memcpy(&receivedDataTH, buf, sizeof(receivedDataTH));

        // Send temperature and humidity values separately over Bluetooth
        bluetoothSerial.print("T:");
        bluetoothSerial.println(receivedDataTH.temperature);
        bluetoothSerial.print("H:");
        bluetoothSerial.println(receivedDataTH.humidity);

        // Output to serial monitor for debugging
        Serial.print("Received Temperature: ");
        Serial.println(receivedDataTH.temperature);
        Serial.print("Received Humidity: ");
        Serial.println(receivedDataTH.humidity);
      } else if (deviceKey == definedDeviceKeyGas && buflen == sizeof(SensorDataGas)) { // Check if received data is gas detector value
        SensorDataGas receivedDataGas;
        memcpy(&receivedDataGas, buf, sizeof(receivedDataGas));

        if (receivedDataGas.gasValue == 0) {
          // Send gas value over Bluetooth
          bluetoothSerial.print("G:");
          bluetoothSerial.println("Howply");
          soundBuzzer();
        }
        else {
          // Send gas value over Bluetooth
          bluetoothSerial.print("G:");
          bluetoothSerial.println("Kadaly");
          digitalWrite(buzzer, LOW);
        }

        // Output to serial monitor for debugging
        Serial.print("Received Gas Value: ");
        Serial.println(receivedDataGas.gasValue);
      } else if (deviceKey == definedDeviceKeyFire && buflen == sizeof(SensorDataFire)) { // Check if received data is fire sensor value
        SensorDataFire receivedDataFire;
        memcpy(&receivedDataFire, buf, sizeof(receivedDataFire));

        if (receivedDataFire.fireValue == 0) {
          // Send gas value over Bluetooth
          bluetoothSerial.print("F:");
          bluetoothSerial.println("Howply");
          soundBuzzer();
        }
        else {
          // Send gas value over Bluetooth
          bluetoothSerial.print("F:");
          bluetoothSerial.println("Kadaly");
          digitalWrite(buzzer, LOW);
        }

        //        // Send fire value over Bluetooth
        //        bluetoothSerial.print("F:");
        //        bluetoothSerial.println(receivedDataFire.fireValue);

        // Output to serial monitor for debugging
        Serial.print("Received Fire Value: ");
        Serial.println(receivedDataFire.fireValue);
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
// 00:18:E4:40:00:06
