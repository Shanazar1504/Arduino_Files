#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "Make DIY";
const char* password = "210302";
ESP8266WebServer server(80);

void setup() {

Serial.begin(115200);
 WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);

 IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

}

  void loop() {
    server.handleClient();
    
      command = server.arg("State");
      

  }
