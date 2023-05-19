#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

long randNumber;

int ThermistorPin = A0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf, Tlc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int sensorValue = 0;  // variable to store the value coming from the sensor

const char* ssid = "Admin";
const char* password = "admin123";

//IPAddress staticIP(192, 168, 1, 177); //ESP static ip
//IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
//IPAddress subnet(255, 255, 255, 0);  //Subnet mask
//IPAddress dns(8, 8, 8, 8);  //DNS

ESP8266WebServer server(80);

void returnTemp() {
  server.send(200, "text/html", "" + String(Tc)); 
}
void returnHeart() {
  server.send(200, "text/html", "" + String(randNumber));
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
//  WiFi.config(staticIP , gateway, subnet, dns);

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
  server.on("/checkTemp/", returnTemp);
  server.on("/checkHeart/", returnHeart);
  server.begin();
  Serial.println("Server started");

}
void loop() {
  server.handleClient();
  tempeee();
  heartt();
}

void tempeee() {
  // read the value from the sensor:
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  Tlc = (Tc * (-1));
  Tf = (Tlc * 9.0) / 5.0 + 32.0;
  Serial.print("Temperature: ");
  Serial.print(Tc);
  Serial.println(" C");
  delay(3000);
}
void heartt() {
  randNumber = random(70, 96);
  Serial.println(randNumber);
  delay(5000);
}
