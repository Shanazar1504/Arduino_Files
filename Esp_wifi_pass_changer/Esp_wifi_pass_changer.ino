#include <ESP8266WiFi.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

String device_key = "Light";

ESP8266WebServer server(80);

const int Relay1 = 2;
const int Input = 0;

int val;
int btnstate = 0;
String mystring = String(btnstate);

void handlePong() {
  server.send(200, "text/html", device_key);

  // Create a JSON object
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["name"] = device_key;
  jsonDoc["ip"] =  WiFi.localIP();


  // Convert the JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send the POST request
  sendPostRequest(jsonString);
}

void response() {
  server.send(200, "text/html", mystring);
  digitalWrite(Relay1, HIGH);
  delay(100);
  digitalWrite(Relay1, LOW);
}


void setup() {
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);
  pinMode(Input, INPUT);
  digitalWrite(Relay1, LOW);

  // Create an instance of WiFiManager
  WiFiManager wifiManager;

  // Uncomment the next line for a quick initial setup
  // wifiManager.resetSettings();

  // Set up custom parameters for configuration
  // WiFiManagerParameter custom_text("<label>", "<id>", "<default>", "<length>");
  // wifiManager.addParameter(custom_text);

  // Try to connect to the saved WiFi credentials
  if (!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    // Reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  // If you get here, you have connected to the WiFi
  Serial.println("Connected to WiFi!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");

  server.on("/ping/", handlePong);
  server.on("/control/", response);
}

void loop() {
  server.handleClient();
  val = digitalRead(Input);
  //    Serial.println(val);
  if (val == 1) {
    btnstate = 1;
  }
  else if (val == 0) {
    btnstate = 0;
  }
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
