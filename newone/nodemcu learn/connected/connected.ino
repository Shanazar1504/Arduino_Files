#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char* ssid = "210302";
const char* password = "210302";

ESP8266WebServer server(80);

void setup(){
  Serial.begin(9600);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  WiFi.softAP(password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  WiFi.disconnect();
  Serial.println("START");
  WiFi.begin("2103");
  while((!(WiFi.status() == WL_CONNECTED))){
  delay(300);
  }Serial.println("Connected");
  Serial.println("Your ip is:");
  Serial.println((WiFi.localIP()));
  Serial.println("Your gateway is:");
  Serial.println((WiFi.gatewayIP().toString().c_str()));
  Serial.println("Your host name is:");
  Serial.println((WiFi.hostname()));
  
}
void loop()
{
  
}
