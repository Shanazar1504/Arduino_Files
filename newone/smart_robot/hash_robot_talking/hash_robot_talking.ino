
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
WiFiClient client;
ESP8266WebServer server(80); /* defining server port */


const char* ssid = "Smart_robot"; /* Your SSID */
const char* password = "21032002"; /* Your Password */

String  data = "";


void setup()
{
  Serial.begin(115200);
  Serial.println("GPIO test!");


  connectToWiFi();

  server.on("/", handleRequest);
  server.onNotFound(handleRequest);

  /* Starting Server */
  server.begin();
  Serial.println("Server started");

}

void loop() {
  server.handleClient();
  data = server.arg("data");

  if (data != "") {

    if (data.equalsIgnoreCase("set alarm") || data.equalsIgnoreCase("salaam") || data.equalsIgnoreCase("alarm") || data.equalsIgnoreCase("salon")) {
     
  data = "";
}
  }


/* Reuest and resonse handling */
void handleRequest() {
  if ( server.hasArg("data") ) {
    Serial.println(server.arg("Key"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void connectToWiFi() {
  delay(3000);
  WiFi.disconnect();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(500);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  Serial.println("\n");
  delay(5000);
}
