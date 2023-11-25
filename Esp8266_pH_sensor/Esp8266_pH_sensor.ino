#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Akylly_Ahal";
const char* password = "ahal@!85";

// Your Domain name with URL path or IP address with path
String serverName = "http://192.168.31.201:5000/api/post_et";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  float sensorValue = readFloatFromSerial();

  // Create a JSON object
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["mukdar"] = sensorValue;

  // Convert the JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send the POST request
  sendPostRequest(jsonString);

}

float readFloatFromSerial() {
  Serial.println("Enter float value on Serial monitor:");

  while (!Serial.available()) {
    delay(100);
  }

  String input = Serial.readStringUntil('\n');
  input.trim();

  float floatValue = input.toFloat();
  Serial.print("Received float value: ");
  Serial.println(floatValue, 2);  // Print the received float value with 2 decimal places

  return floatValue;
}

void sendPostRequest(String payload) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Set the content type to JSON
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    // Send the POST request
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      String response = http.getString();
      Serial.println("Response: " + response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
