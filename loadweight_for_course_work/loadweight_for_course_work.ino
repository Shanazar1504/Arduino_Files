#include <Arduino.h>
#include "HX711.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 14;
const int LOADCELL_SCK_PIN = 12;

float k;
HX711 scale;

String val = "0";

const char* ssid = "Test";
const char* password = "test1234";

ESP8266WebServer server(80);

const int buzzerPin = 4; // Adjust this to the actual pin connected to the buzzer

void returnLoad() {
  Serial.println(val);
  server.send(200, "text/html", "" + val);
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

  pinMode(buzzerPin, OUTPUT);

}
void loop() {
  server.handleClient();
  loaddd();
}

void loaddd() {
  k = scale.get_units(), 1;
  Serial.print("one reading:\t");
  Serial.println(k);
  if (0 < scale.get_units() && scale.get_units() < 50) {
    val = "1";
    Serial.println("az");
    digitalWrite(buzzerPin, HIGH);
    delay(250); // Adjust the duration of the buzzer sound
    digitalWrite(buzzerPin, LOW);
  }
  else if (50 < scale.get_units() && scale.get_units() < 100) {
    val = "2";
  }
  else if (100 < scale.get_units() && scale.get_units() < 150) {
    val = "3";
  }
  else if (150 < scale.get_units() && scale.get_units() < 200) {
    val = "4";
  }
  else if (200 < scale.get_units() && scale.get_units() < 250) {
    val = "5";
  }

  scale.power_down();             // put the ADC in sleep mode
  delay(750);
  scale.power_up();
}
