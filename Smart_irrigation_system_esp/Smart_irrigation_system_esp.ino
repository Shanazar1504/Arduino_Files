#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "your-ssid";
const char* password = "your-password";
const char* serverUrl = "http://your-server.com/update_moisture";

int soilMoisturePin = A0;  // Analog pin for soil moisture sensor
int pumpPin = D1;         // Digital pin for the water pump

void setup() {
  pinMode(soilMoisturePin, INPUT);
  pinMode(pumpPin, OUTPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  int soilMoisture = analogRead(soilMoisturePin);
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  if (soilMoisture < 500) {  // Adjust this threshold based on your soil moisture sensor
    Serial.println("Soil is too dry. Turning on pump.");

    digitalWrite(pumpPin, HIGH);  // Turn on the water pump

    // Send moisture data to server
    sendMoistureData(soilMoisture);
  } else {
    Serial.println("Soil is wet enough. Turning off pump.");
    digitalWrite(pumpPin, LOW);  // Turn off the water pump
  }

  delay(10000);  // Delay for 10 seconds before the next reading
}

void sendMoistureData(int moisture) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = serverUrl + String(moisture);

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("Moisture data sent. HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Failed to send moisture data. HTTP Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Not connected to WiFi. Cannot send moisture data.");
  }
}
