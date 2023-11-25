#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

#define DHTPIN 2 //D4
#define DHTTYPE DHT11 


int low = 16; // D0
int med = 5; // D1
int high = 4; // D2
int tel = 0; // D3

const char* ssid = "test";
const char* password = "12345678";
DHT dht(DHTPIN, DHTTYPE);

float t = 0.0;
float h = 0.0;

ESP8266WebServer server(80);
void returnTemp() {
//  server.send(200, "text/plain", "" + String());
   server.send(200, "text/plain",String(t).c_str());
}

void handleConditioner() {
  String mode_low = server.arg("mode_low_esp");
  String mode_med = server.arg("mode_med_esp");
  String mode_high = server.arg("mode_high_esp");
  String auto_manual_switch = server.arg("switch_esp");

  
  mode_low.trim();
  mode_med.trim();
  mode_high.trim();
  auto_manual_switch.trim();

  if (mode_high == "1"){
    digitalWrite(high,1);
    digitalWrite(tel,0);
    digitalWrite(low,0);
    digitalWrite(med,0);
    Serial.println("high");
  }
  else if (mode_high == "0"){
    digitalWrite(high,0);
  }

  if (mode_med == "1"){
    digitalWrite(med,1);
    digitalWrite(tel,0);
    digitalWrite(low,0);
    digitalWrite(high,0);
    Serial.println("MED");
  }
  else if (mode_med == "0"){
    digitalWrite(med,0);
  }

  if (mode_low == "1"){
    digitalWrite(low,1);
    digitalWrite(tel,0);
    digitalWrite(med,0);
    digitalWrite(high,0);
    Serial.println("low");
  }
  else if (mode_low == "0"){
    digitalWrite(low,0);
  }

  if (auto_manual_switch == "auto"){
    digitalWrite(tel,1);
    Serial.println("autoMode");
  }
  else if (auto_manual_switch == "manual"){
    digitalWrite(tel,0);
    digitalWrite(high,0);
    digitalWrite(low,0);
    digitalWrite(med,0);  
    Serial.println("manualMode");
  }
  server.send(200, "text/html", "ok");
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(tel, OUTPUT);
  pinMode(med, OUTPUT);
  pinMode(low, OUTPUT);
  pinMode(high, OUTPUT);
  digitalWrite(tel, HIGH);


  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  //    WiFi.config(staticIP , gateway, subnet, dns);

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
  Serial.println("Server started");

  server.on("/control/", handleConditioner);
  server.on("/checkTemp/", returnTemp);
  server.begin();

}

void loop() {
  server.handleClient();
  t = dht.readTemperature();
  h = dht.readHumidity();
}
