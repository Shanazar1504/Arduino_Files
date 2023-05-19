#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

const int ledPin = 2;
const int ldrPin = A0;
int brightness1 = 60;
int brightness2 = 120;
int brightness3 = 180;
int brightness4 = 255;

const char* ssid = "LDR";
const char* password = "12345678";
const char* deviceName = "Dimmer";
String payload;
String device_key = "secret";
String command = "dimmer";
String validation_key = "key";

ESP8266WebServer server(80);

String dimmer_input = "<input style=\"height: 200px;width: 600px;font-size: 50px;\" type=\"text\" name=\"dimmer_input\" placeholder=\"ID Key\"></br>";
String submit_input = "<input type=\"submit\" style=\"border-radius: 50px 50px 50px 50px;text-align:center;height:150px;font-size:50px;width:400px;color:white;background-color: #00A8A9\" value=\"Validate\">";


String div_view = "<div>";
String form_view = "<form style=\"margin-top: 180px;display:flex;flex-direction: column;align-items: center;\" action=\"/ulanyjy\" method=\"POST\">";
String form_end_view = "</form></div>";
String html_view = div_view + form_view + dimmer_input + submit_input + form_end_view;


void handlePong() {
  server.send(200, "text/html", device_key);
}


void handleRouteAction() {
  String command = server.arg("command");
  command.trim();
  
  if (command == "0") {
    Serial.println("Dimmer is set 0");
    digitalWrite(ledPin, 0);
    server.send(200, "text/html", html_view);
  }
  else if (command == "1") {
    Serial.println("Dimmer is set 1");
    analogWrite(ledPin, brightness1);
    server.send(200, "text/html", html_view);
  }
  else if (command == "2") {
    Serial.println("Dimmer is set 2");
    analogWrite(ledPin, brightness2);
    server.send(200, "text/html", html_view);
  }
  else if (command == "3") {
    Serial.println("Dimmer is set 3");
    analogWrite(ledPin, brightness3);
    server.send(200, "text/html", html_view);
  }
  else if (command == "4") {
    Serial.println("Dimmer is set 4");
    analogWrite(ledPin, brightness4);
    server.send(200, "text/html", html_view);
  }

  server.send(200, "text/html", "OK");
}

void handleRoot(){
  server.send(200, "text/html", html_view);
}

void handleFormSubmit(){
  if( !server.hasArg("dimmer_input") || server.arg("dimmer_input") == NULL) {
    server.send(200, "text/html", html_view);
    return;
  }
  if (server.arg("dimmer_input") == "0") {
    Serial.println("Dimmer is set 0");
    digitalWrite(ledPin, 0);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "1") {
    Serial.println("Dimmer is set 1");
    analogWrite(ledPin, brightness1);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "2") {
    Serial.println("Dimmer is set 2");
    analogWrite(ledPin, brightness2);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "3") {
    Serial.println("Dimmer is set 3");
    analogWrite(ledPin, brightness3);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "4") {
    Serial.println("Dimmer is set 4");
    analogWrite(ledPin, brightness4);
    server.send(200, "text/html", html_view);
  }
  else {
    server.send(200, "text/html", html_view);
  }
}


void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  
  server.on("/ping/", handlePong);
  server.on("/control/", handleRouteAction);
  server.on("/validation/", handleRoot);
  server.on("/ulanyjy", handleFormSubmit);
  server.begin();
}

void loop() {
  server.handleClient();

  int ldrStatus = analogRead(ldrPin);

  int cycle = ldrStatus * (255 / 1023.0);

  analogWrite(ledPin, cycle);

   int dutyCycle;

	 if (ldrStatus >= 50) {
     for(dutyCycle = ldrStatus; dutyCycle < brightness1; dutyCycle++){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(ldrStatus + "bright 1");
	 } 
  
   else if (ldrStatus >= 300) {
     for(dutyCycle = ldrStatus; dutyCycle < brightness2; dutyCycle++){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(ldrStatus + "bright 2");
   }
  
    else if (ldrStatus >= 600) {
     for(dutyCycle = ldrStatus; dutyCycle < brightness3; dutyCycle++){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(ldrStatus + "bright 3");
   } 
  
   else if (ldrStatus >= 800) {
     for(dutyCycle = ldrStatus; dutyCycle < brightness4; dutyCycle++){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(ldrStatus + "bright 4");
   }
  
    else if (ldrStatus <= 40) {
     for(dutyCycle = ldrStatus; dutyCycle > 0; dutyCycle--){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(ldrStatus + "bright 0");
   }

}




void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
