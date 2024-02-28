// DHT 11
// Created by Shanazar(Shanny)
// 29.01.2024  13:30

#include <RH_ASK.h>
#include <SPI.h>
#include <DHT.h>

RH_ASK rf_driver;

const int transmitPin = 12; // Define the pin connected to the RF transmitter module
const uint8_t deviceKey = 101; // Define the device key

#define DHTPIN 3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  if (!rf_driver.init())
    Serial.println("RF driver init failed");

  pinMode(transmitPin, OUTPUT); // Set the data pin as output
  dht.begin(); // Initialize the DHT sensor
}

void loop() {
  // Read temperature and humidity from the DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% - Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Create a byte array to hold the sensor data and device key
  uint8_t data[sizeof(humidity) + sizeof(temperature) + sizeof(deviceKey)];

  // Copy the device key into the byte array
  memcpy(data, &deviceKey, sizeof(deviceKey));

  // Copy the humidity value into the byte array after the device key
  memcpy(data + sizeof(deviceKey), &humidity, sizeof(humidity));

  // Copy the temperature value into the byte array after the humidity
  memcpy(data + sizeof(deviceKey) + sizeof(humidity), &temperature, sizeof(temperature));

  // Send the byte array
  rf_driver.send(data, sizeof(data));
  rf_driver.waitPacketSent();

  delay(1000); // Delay before sending the next message
}
