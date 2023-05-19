#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const int Relay1 = 4;

const char* ssid = "Test";
const char* password = "12345678";

ESP8266WebServer server(80);
void returnCheck() {
  server.send(200, "text/html", "Ishleyar" );
}
void Relay1on() {
  server.send(200, "text/html", "Relay_1_on");
  digitalWrite(Relay1, HIGH);
  Serial.println("s1_on");
}
void Relay1off() {
  server.send(200, "text/html", "Relay_1_off");
  digitalWrite(Relay1, LOW);
  Serial.println("s1_off");
}

void setup() {
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay1, LOW);

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
  server.on("/Relay_1_on/", Relay1on);
  server.on("/Relay_1_off/", Relay1off);
}

void loop() {
  server.handleClient();
}
