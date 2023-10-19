#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#define DHTPIN 5
#define DHTTYPE DHT11

#define toprak_cyg A0
#define high 600
int suw = 2;
int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 1000;
boolean lockLow = true;
boolean takeLowTime;

float temp;
float hum;
int value_toprak_cyg;

const char *ssid = "gidro";
const char *password = "12345678";

ESP8266WebServer server(80);
void returnCheck() {
  server.send(200, "text/html", "" + String(temp));
}
void returnTop_cyg() {
  server.send(200, "text/html", "" + String(value_toprak_cyg));
}
void returnHum() {
  server.send(200, "text/html", "" + String(hum));
}
void suw_on() {
  server.send(200, "text/html", "suw_on");
  digitalWrite(suw, LOW);
  Serial.println("l1");
}
void suw_off() {
  server.send(200, "text/html", "suw_off");
  digitalWrite(suw, HIGH);
  Serial.println("l2");
}

  unsigned long previousMillis = 0;
  unsigned long interval = 3000;

  DHT dht(DHTPIN, DHTTYPE);

  void setup() {
    Serial.begin(115200);
    dht.begin();
    pinMode(toprak_cyg, INPUT);
    pinMode(suw, OUTPUT);
    digitalWrite(suw, HIGH);

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
    server.begin();
    Serial.println("Server started");
    server.on("/Temp/", returnCheck);
    server.on("/top_cyg/", returnTop_cyg);
    server.on("/Hum/", returnHum);
    server.on("/SUW0n/", suw_on);
    server.on("/SUW0ff/", suw_off);

  }

  void loop() {
    server.handleClient();
    dhtt();
    top_cyg();
    delay(300);
  }
  void dhtt() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      //read humidity and publish to android app
      hum = dht.readHumidity();
      //read temperature and publish to android app
      temp = dht.readTemperature();
    }
  }
void top_cyg() {
    int value_toprak_cyg = analogRead(toprak_cyg);
    Serial.println(value_toprak_cyg);
  }
