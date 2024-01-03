#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

//Static IP address configuration
IPAddress staticIP(192, 168, 0, 246); //ESP static ip
IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "Link_9860";
const char* password = "test12345";
const char* deviceName = "tvv";
String serverUrl = "192.168.0.252";
String payload;
String device_key = "some_magic_word_2";
//String command = "watt_measurer";

ESP8266WebServer server(80);

String stream;


void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
 
  WiFi.mode(WIFI_STA);
 
//  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
//  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/ping/", handlePong);
  server.on("/control/", sendDataFromMaster);
 
  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
 // sendDataFromMaster();
}
/*
void handleDevice(){
  String command = server.arg("command");
  
  
}*/

void sendDataFromMaster(){
  String command = server.arg("command");
 
  command.trim();
  if (command.length()>0){
    Serial.println(command);
   // String argument_data = "?device_key="+device_key+"&command="+command+"&value="+String(stream);
    //sendRequest("http://"+serverUrl+"/esp/ArgToDB/",argument_data);
  }
 // command="";
 server.send(200, "text/plain", "ok");
}



//void sendRequest(String path, String sendingData){
//  if(WiFi.status()== WL_CONNECTED){
//    String serverPath = path+sendingData;
//    Serial.println(serverPath);
//    payload = httpGETRequest(serverPath.c_str());
//    Serial.println(payload);
//  }
//  else {
//    Serial.println("WiFi Disconnected");
//  }
//}
//
//
//String httpGETRequest(const char* serverName) {
//  HTTPClient http;
//  http.begin(serverName);
//  int httpResponseCode = http.GET();  
//  String payload = "{}"; 
//  if (httpResponseCode>0) {
//    Serial.print("HTTP Response code: ");
//    Serial.println(httpResponseCode);
//    payload = http.getString();
//  }
//  else {
//    Serial.print("Error code: ");
//    Serial.println(httpResponseCode);
//  }
//  http.end();
//  return payload;
//}
