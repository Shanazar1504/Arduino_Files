/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>

#include <Arduino.h>
#include <ESP8266WebServer.h>

// #include "secrets.h"  // add WLAN Credentials in here.

#include <FS.h>        // File System for Web Server Files
#include <LittleFS.h>  // This file system is used.

#ifndef STASSID
#define STASSID "Bet"
#define STAPSK "2002...."
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.98";
const uint16_t port = 9000;


ESP8266WebServer server(8090);

void handleLight() {
  digitalWrite(4, HIGH); 
  delay(500);
   digitalWrite(4, LOW); 

  Serial.print("Ocurdim");
  
  // TRACE("Redirect...");
  // String url = "/index.htm";

 // if (!LittleFS.exists(url)) { url = "/$update.htm"; }

  //server.sendHeader("Location", url, true);
  server.send(200);
}  
void diasbleLight() {
  digitalWrite(4, LOW); 
   delay(500);
  Serial.print("Yakdym");
  // TRACE("Redirect...");
  // String url = "/index.htm";

 // if (!LittleFS.exists(url)) { url = "/$update.htm"; }

  //server.sendHeader("Location", url, true);
  server.send(200);
}  
// need a WebServer for http access on port 80.

void setup() {
   delay(3000);
  Serial.begin(115200);
  pinMode(4, OUTPUT);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
         digitalWrite(LED_BUILTIN, HIGH);

    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // register a redirect handler when only domain name is given.
  server.on("/H", HTTP_GET, handleLight);
  server.on("/L", HTTP_GET, diasbleLight);
  server.begin();
}

void loop() {
server.handleClient();
// Serial.print("loopyn ici");
  // WiFiClient client = server.available();
  // static bool wait = false;
  // if()
  // {

  // }
  

  // Serial.print("connecting to ");
  // Serial.print(host);
  // Serial.print(':');
  // Serial.println(port);

  // Use WiFiClient class to create TCP connections
  // WiFiClient client;
  // if (!client.connect(host, port)) {
  //   Serial.println("connection failed");
  //   delay(5000);
  //   return;
  // }

  // // This will send a string to the server
  // Serial.println("sending data to server");
  // if (client.connected()) { client.println("hello from ESP8266"); }

  // // wait for data to be available
  // unsigned long timeout = millis();
  // while (client.available() == 0) {
  //   if (millis() - timeout > 5000) {
  //     Serial.println(">>> Client Timeout !");
  //     client.stop();
  //     delay(60000);
  //     return;
  //   }
  // }

  // // Read all the lines of the reply from server and print them to Serial
  // Serial.println("receiving from remote server");
  // // not testing 'client.connected()' since we do not need to send data here
  // while (client.available()) {
  //   char ch = static_cast<char>(client.read());
  //   Serial.print(ch);
  // }

  // // Close the connection
  // Serial.println();
  // Serial.println("closing connection");
  // client.stop();

  // if (wait) {
  //   delay(300000);  // execute once every 5 minutes, don't flood remote service
  // }
  // wait = true;
}
