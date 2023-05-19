
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include <Arduino.h>
#include "HX711.h"


ESP8266WebServer server(80);

long randNumber;

const char *ssid = "Test";
const char *password = "12345678";

String agram;

const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

const int buzzer = 5;

unsigned long previousMillis = 0;
unsigned long interval = 1000;

HX711 scale;

void returnScale() {
  server.send(200, "text/html", "" + String(scale.get_units()));
}
void returnHeart() {
  server.send(200, "text/html", "" + String(randNumber));
}
void returnNot() {
  server.send(200, "text/html", "Notification");
}

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  //    WiFi.config(staticIP , gateway, subnet, dns);

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
  server.begin();
  Serial.println("Server started");
  server.on("/checkScale/", returnScale);
  server.on("/checkHeart/", returnHeart);
  server.on("/checkNott/", returnNot);

  scale.set_scale(729.414);
  scale.tare();
}

void loop() {
  server.handleClient();
  //  tempeee();
  if (0 < scale.get_units() ) {
    Serial.println(scale.get_units());
  };
  if (40 < scale.get_units() && scale.get_units() < 50 ) {
    Serial.println("Duýduryş");
    last();
  }
  //  if (15 < scale.get_units() && scale.get_units() < 50) {
  //    agram = "1";
  //  };
  //  if (50 < scale.get_units() && scale.get_units() < 100) {
  //    agram = "2";
  //  };
  //  if (100 < scale.get_units() && scale.get_units() < 150) {
  //    agram = "3";
  //  };
  //  if (150 < scale.get_units() && scale.get_units() < 200) {
  //    agram = "4";
  //  };
  //  if (200 < scale.get_units() && scale.get_units() < 250) {
  //    agram = "5";
  //  };
  //  if (250 < scale.get_units() && scale.get_units() < 300) {
  //    agram = "6";
  //  };
  //  if (300 < scale.get_units() && scale.get_units() < 350) {
  //    agram = "7";
  //  };
  //  if (350 < scale.get_units() && scale.get_units() < 400) {
  //    agram = "8";
  //  };
  //  if (400 < scale.get_units() && scale.get_units() < 450) {
  //    agram = "9";
  //  };
  //  if (450 < scale.get_units() && scale.get_units() < 550) {
  //    agram = "10";
  //  };

  scale.power_down();             // put the ADC in sleep mode
  delay(2000);
  scale.power_up();

  heartt();
}

void heartt() {
  randNumber = random(70, 96);
  Serial.println(randNumber);
  delay(5000);
}
void last() {
  digitalWrite(buzzer, 1);
  delay(1000);
  digitalWrite(buzzer, 0);
  delay(1000);
  digitalWrite(buzzer, 1);
  delay(1000);
  digitalWrite(buzzer, 0);
}
