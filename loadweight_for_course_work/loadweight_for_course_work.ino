#include <Arduino.h>
#include "HX711.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 14;

float k;
HX711 scale;

const char* ssid = "Admin";
const char* password = "bionics123";

ESP8266WebServer server(80);

void returnLoad() {
  if (k > 0) {
    server.send(200, "text/html", "" + String(k));
  }
  else{
    server.send(200, "text/html", "0");
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
//  WiFi.config(staticIP , gateway, subnet, dns);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  server.on("/checkLoad/", returnLoad);
  server.begin();
  Serial.println("Server started");
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(199.558);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

}
void loop() {
  server.handleClient();
  loaddd();
}

void loaddd() {
  k = scale.get_units(), 1;
  Serial.print("one reading:\t");
  // Serial.print(scale.get_units(), 1);
  if (scale.get_units() > 0) {
    Serial.println(k);
  }
  scale.power_down();             // put the ADC in sleep mode
  delay(3000);
  scale.power_up();
}
