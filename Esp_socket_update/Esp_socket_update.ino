#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

String device_key = "Socket";
String myString; // Declare myString globally

ESP8266WebServer server(80);

const int Relay1 = 2;
const int Input = 0;

int val;
int btnstate;

void handlePong() {
  server.send(200, "text/html", device_key);
}

void state() {
  // Convert int to string inside the state function
  myString = String(val);
  server.send(200, "text/html", myString);
}

void response() {
  server.send(200, "text/html", "Device is working");
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
  server.on("/state/", state);
}

void loop() {
  server.handleClient();
  val = digitalRead(Input);
  Serial.println(val);
  if (val == 1) {
    btnstate = 1;
  }
  else if (val == 0) {
    btnstate = 0;
  }
  // You can also add a delay here if needed
}
