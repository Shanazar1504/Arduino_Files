#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "TP-Link_9860";
const char* password = "test12345";

// Set your static IP address
IPAddress staticIP(192, 168, 1, 72); // Set your desired static IP address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  // Define server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/led/on", HTTP_GET, handleLedOn);
  server.on("/led/off", HTTP_GET, handleLedOff);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP8266!");
}

void handleLedOn() {
  // Add code to turn on an LED or perform any other desired action
  server.send(200, "text/plain", "LED turned on");
}

void handleLedOff() {
  // Add code to turn off an LED or perform any other desired action
  server.send(200, "text/plain", "LED turned off");
}
