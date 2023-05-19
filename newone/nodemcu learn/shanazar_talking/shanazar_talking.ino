#include <Arduino.h>
#include "Wire.h"
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"
#include "audiodata.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
WiFiClient client;
ESP8266WebServer server(80);

const char* ssid = "OGUZHAN"; 
const char* password = "1020304050";
String  data = "";
Servo myservo;  

void setup() {
 myservo.attach(0);/* Pin D3 */
 
    Serial.begin(115200);
  Serial.println("GPIO test!");
    connectToWiFi();

      server.on("/", handleRequest);
  server.onNotFound(handleRequest);

  server.begin();
  Serial.println("Server started");

}

void loop() {
  int pos;

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
