// Author : Mudassar Tamboli
// Date   : 6/8/2018

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>   

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);
WiFiClient wifiClient;


String ipAddress;
int newValue, endValue, cycle;
boolean activator = true;
unsigned long previousMillis = 0;
unsigned long interval = 30000;

//LDR sensor pins
const int ldrPin = A0;
const int ledPin = 2;


void setup() {
    Serial.begin(115200);

  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
    initWifiStation();

    server.on("/set/", setValue);
    server.on("/activate/", activate);
    server.on("/deactivate/", deactivate);
    server.on("/add", handleSpecificArg);
    server.on("/catch/", catchData);
} 

void loop() {
    server.handleClient();

    unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    initWifiStation();
    previousMillis = currentMillis;
  } 

  int ldrStatus = analogRead(ldrPin);

  cycle = ldrStatus * (255 / 1023.0);
  cycle = map(cycle, 0, 255, 255, 0);

  if(activator == true) {
    analogWrite(ledPin, cycle);
    Serial.println(cycle);
    
  }
  
  delay(10);
}


void activate() {
  activator = true;
  server.send(200, "text/html", "activated");
}

void deactivate() {
  activator = false;
  server.send(200, "text/html", "deactivated");
}

void catchData() {
//  int sendCycle = map(cycle, 255, 0, 0, 255);
  String sendCycleStr = String(cycle);
  server.send(200, "text/html", sendCycleStr);
}

//############### GETTING DATA FROM DEVICE WITH LOCALHOST #####################//
void setValue() {
  
  if(newValue > endValue) {
     for(; newValue >= endValue; newValue--){ 
        analogWrite(ledPin, newValue);
        Serial.println(newValue);
        delay(10);
     } 
  } else {
     for(; newValue <= endValue; newValue++){ 
        analogWrite(ledPin, newValue);
        Serial.println(newValue);
        delay(10);
     } 
  }

  server.send(200, "text/html", "new value: " + newValue);
}



//############### ADD TOKEN WITH LOCALHOST #####################//

void handleSpecificArg() { 
  String message = "";
  if (server.arg("value") == ""){     //Parameter not found
    message = "0"; //token not found
    }else{     //Parameter found
    message += server.arg("value");     //Gets the value of the query parameter
    endValue = message.toInt();
  }
  server.send(200, "text/html", "end value: " + endValue);          //Returns the HTTP response
}



//############### INIT WIFI STATION #####################//
void initWifiStation() {
    delay(10);
    Serial.println('\n');
    wifiMulti.addAP("smart", "12345678");   // add Wi-Fi networks you want to connect to
//    wifiMulti.addAP("LDR", "12345678");
    wifiMulti.addAP("TP-LINK_BF4C", "1020304050");
    Serial.println("Connecting ...");
    int i = 0;
    while (wifiMulti.run() != WL_CONNECTED) {
       delay(1000);        
       Serial.print(".");
    }
  WiFi.hostname("LDR ULGAMY");
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  ipAddress = WiFi.localIP().toString();
  server.begin();
//  Serial.println("HTTP server started");
}
