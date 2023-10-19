#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "your_network_ssid";
const char* password = "your_network_password";
const char* url = "http://your_url";
String data = "your_string_data";

HTTPClient http;

void setup() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {


    http.begin(WiFiClient,url);  // Specify the URL
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Set the content type

    int httpResponseCode = http.POST(data); // Send the POST request and get the response

    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response payload

      Serial.println(httpResponseCode); // Print the HTTP response code
      Serial.println(response); // Print the response payload
    }
    else {
      Serial.println("Error posting data");
    }

    http.end(); // Close the connection

    delay(3000); // Delay before sending the next request
  }
}
