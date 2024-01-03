#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const int Relay1 = 4;
const int Relay2 = 5;
const int Relay3 = 16;

const char* ssid = "Test";
const char* password = "test1234";

ESP8266WebServer server(80);
void returnCheck() {
  server.send(200, "text/html", "Ishleyar" );
}
void Relay1on() {
  server.send(200, "text/html", "Relay_1_on");
  digitalWrite(Relay1, HIGH);
  Serial.println("s1_on");
}
void Relay2on() {
  server.send(200, "text/html", "Relay_2_on");
  digitalWrite(Relay2, HIGH);
  Serial.println("s2_on");
}
void Relay3on() {
  server.send(200, "text/html", "Relay_3_on");
  digitalWrite(Relay3, HIGH);
  Serial.println("s3_on");
}
void Relay1off() {
  server.send(200, "text/html", "Relay_1_off");
  digitalWrite(Relay1, LOW);
  Serial.println("s1_off");
}
void Relay2off() {
  server.send(200, "text/html", "Relay_2_off");
  digitalWrite(Relay2, LOW);
  Serial.println("s2_off");
}
void Relay3off() {
  server.send(200, "text/html", "Relay_3_off");
  digitalWrite(Relay3, LOW);
  Serial.println("s3_off");
}

void setup() {
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
  digitalWrite(Relay3, LOW);


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
  server.on("/light_on/", Relay1on);
  server.on("/tefal_on/", Relay2on);
  server.on("/heat_on/", Relay3on);
  server.on("/light_off/", Relay1off);
  server.on("/tefal_off/", Relay2off);
  server.on("/heat_off/", Relay3off);
}

void loop() {
  server.handleClient();
}
