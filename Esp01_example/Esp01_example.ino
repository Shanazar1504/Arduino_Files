#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

const char* ssid = "ELECTRONICLAB";
const char* password = "Electronic123";

const int Relay1 = 0;

ESP8266WebServer server(80);

String stream;


void handlePong() {
  server.send(200, "text/html", "ESP_SMART_CITY");
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
    if (command == "light_on") {
      digitalWrite(Relay1, HIGH);
    }
    else  if (command == "light_off") {
      digitalWrite(Relay1, LOW);
    }
    Serial.println(command);
    // String argument_data = "?device_key="+device_key+"&command="+command+"&value="+String(stream);
    //sendRequest("http://"+serverUrl+"/esp/ArgToDB/",argument_data);
  }
  // command="";
  server.send(200, "text/plain", "ok");
}
