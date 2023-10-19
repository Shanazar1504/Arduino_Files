#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

const char* ssid = "Test";
const char* password = "test1234";

ESP8266WebServer server(80);

String stream;


void handlePong() {
  server.send(200, "text/html", "Ishleyar");
}


void setup() {
 Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
//      WiFi.config();

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
  server.on("/ping/", handlePong);
  server.on("/control/", sendDataFromMaster);


}


void loop() {
  server.handleClient();
  // sendDataFromMaster();
}
/*
  void handleDevice(){
  String command = server.arg("command");


  }*/

void sendDataFromMaster() {
  String command = server.arg("command");

  command.trim();
  if (command.length() > 0) {
    Serial.println(command);
    // String argument_data = "?device_key="+device_key+"&command="+command+"&value="+String(stream);
    //sendRequest("http://"+serverUrl+"/esp/ArgToDB/",argument_data);
  }
  // command="";
  server.send(200, "text/plain", "ok");
}
