#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


ESP8266WebServer server(80);

void returnDht() {

}

void returnFire() {

}
void returnGas() {

}


const char* ssid = "Test";
const char* password = "test12345";

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
  server.on("/checkDht/", returnDht);
  server.on("/checkGas/", returnGas);
  server.on("/checkFire/", returnFire);

  server.begin();
  Serial.println("Server started");
}

void loop () {
  if (Serial.available() != 0) {
    String input = Serial.readStringUntil('\n');
    Serial.println(input);
    input.trim();
    //  kk = input.toFloat();
    //  Serial.println(kk, 2);

  }
}
