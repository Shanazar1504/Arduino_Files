
// Including the ESP8266 WiFi library
#include <ESP8266WiFi.h>
#include "DHT.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Replace with your network details
const char* ssid = "Linux";
const char* password = "88888888";

const char* kadaly = "kadaly";
const char* yaramaz = "yaramaz";
const char* umumy; 

// Web Server on port 80
WiFiServer server(80);

// DHT Sensor
const int DHTPin = 5;
const int smoke = A0;
const int ses = 4;
const int buzzer = 2;
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);
  pinMode(smoke, INPUT);
  pinMode(ses, INPUT);
  pinMode(buzzer, OUTPUT);
  dht.begin();

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Starting the web server
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(1000);

  // Printing the ESP IP address
  Serial.println(WiFi.localIP());
}

// runs over and over again
void loop() {
  // Listenning for new clients
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c == '\n' && blank_line) {
          // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          float s = analogRead(smoke);
          float ses_val = digitalRead(ses);

          if(ses_val == 0){
            umumy = yaramaz;
          }else{
            umumy = kadaly;
          }

          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // your actual web page that displays temperature and humidity
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head></head><body><h1>Dokma karhanasynyn icki gursawynyn maglumaty</h1><h3>Howanyn temperaturasy: ");
          client.println(t);
          client.println("*C</h3><h3>Zyyanly gazlaryn mukdary: ");
          client.println(s);
          client.println("PM</h3><h3>Howanyn cyglylygy: ");
          client.println(h);
          client.println("%</h3><h3>");
          client.println("</body></html>");
          client.println("</h3><h3>Sesin tony: ");
          client.println(umumy);
          client.println("</h3><h3>");
          client.println("</body></html>");

          break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}
