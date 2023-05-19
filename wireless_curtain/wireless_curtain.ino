#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

const char* ssid = "Test";
const char* password = "12345678";

ESP8266WebServer server(80);

String stream;

void returnCheck() {
  server.send(200, "text/html", "Ishleyar" );
}

void go_up() {
  server.send(200, "text/html", "up" );
  up();
}

void go_down() {
  server.send(200, "text/html", "down" );
  down();
}

void setup() {
  Serial.begin(115200);

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
  server.on("/check/", returnCheck);
  server.on("/GO_UP/", go_up);
  server.on("/GO_DOWN/", go_down);
}

void loop() {
  server.handleClient();
}

void up() {
  Serial.println("1");
}

void down() {
  Serial.println("2");
}
