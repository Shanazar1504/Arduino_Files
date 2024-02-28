#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>


//Static IP address configuration
IPAddress staticIP(192, 168, 1, 14); //ESP static ip
IPAddress gateway(192, 168, 43, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS

const char* ssid = "user";
const char* password = "12345678";
const char* deviceName = "Waiter";
String serverUrl = "192.168.43.252";
String payload;
String device_key = "Waiter_for_booking";


ESP8266WebServer server(80);

String stream;



void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup() {

Serial.begin(115200);
    // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
      WiFi.config(staticIP , gateway, subnet, dns);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  Serial.println("");
  }
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  server.begin();
  Serial.println("Server started");

  server.on("/ping/", handlePong);
  server.on("/control/", SendDataToArduino);
  server.enableCORS(true);
//  server.sendHeader("Allow","*");
//  server.sendHeader("Access-Control-Allow-Origin","*");
//  server.sendHeader("Access-Control-Allow-Methods","*");
//  server.sendHeader("Access-Control-Allow-Headers","*");
  server.begin();
  Serial.println("HTTP server started");
      
}

void loop() {
  server.handleClient();
}

void SendDataToArduino() {
  String command = server.arg("command");
 
  command.trim();
  if (command.length()>0){
    Serial.println(command);
  }
  server.send(200, "text/plain", "ok");
}
