//for only smartcar don't copy it

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);

const char *mqtt_broker = "192.168.1.108";
//const char *mqtt_broker = "mqtt.flespi.io";
//const char *mqtt_username = "5KLDuAGlmqXuNH53pzJW51SqAnyo452YFBrX1V6dbUwNppGEPdoI46WsilGaewYI";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *topic = "device";

int stopper = 4;
int engine = 2;
int light = 0;
int enbA = 5;
int motA = 15;
int motB = 13;

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void setup() {
  Serial.begin(115200);
  pinMode(stopper, OUTPUT);
  pinMode(engine, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(motA, OUTPUT);
  pinMode(motB, OUTPUT);


  server.on("/activate/", activate);
  server.on("/deactivate/", deactivate);

  initWifiStation();
  initMQTTClient();

  digitalWrite(stopper, 0);
  digitalWrite(engine, 0);
  digitalWrite(light, 0);
  digitalWrite(enbA, 0);
  digitalWrite(motA, 0);
  digitalWrite(motB, 0);

  client.subscribe(topic);
}

void loop() {
  client.loop();
  server.handleClient();

  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    initWifiStation();
    previousMillis = currentMillis;
  }
}

void activate() {
  mqtt_broker = "mqtt.flespi.io";

  initMQTTClient();
  server.send(200, "text/html", "activated");

}

void deactivate() {
  mqtt_broker = "192.168.1.108";

  initMQTTClient();
  server.send(200, "text/html", "deactivated");
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char) payload[i];
    // convert *byte to string
  }
  if (message == "1") {
    //    Serial.println("Mator yandy");
    digitalWrite(engine, 1);
  }
  else if (message == "2") {
    //    Serial.println("Mator ocdi");
    digitalWrite(engine, 0);
  }
  else if (message == "19") {
    accidenton();
  }
  else if (message == "20") {
    accidentoff();
  }
  else if (message == "13") {
    digitalWrite(light, 1);
  }
  else if (message == "14") {
    digitalWrite(light, 0);
  }
  else if (message == "00") {
    Serial.println("geldi");
    digitalWrite(enbA, 0);
    digitalWrite(motA, 0);
    digitalWrite(motB, 0);
  }
  else if (message == "01") {
    Serial.println("mode1");
    digitalWrite(enbA, 55);
    digitalWrite(motA, 1);
    digitalWrite(motB, 0);
  }
  else if (message == "02") {
    Serial.println("mode2");
    digitalWrite(enbA, 130);
    digitalWrite(motA, 1);
    digitalWrite(motB, 0);
  }
  else if (message == "03") {
    Serial.println("mode3");
    digitalWrite(enbA, 195);
    digitalWrite(motA, 1);
    digitalWrite(motB, 0);
  }
  else if (message == "04") {
    Serial.println("mode4");
    digitalWrite(enbA, 255);
    digitalWrite(motA, 1);
    digitalWrite(motB, 0);
  }
}

void accidentoff () {
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
  digitalWrite(stopper, 1);
  delay(500);
  digitalWrite(stopper, 0);
  delay(500);
}

void accidenton() {
  digitalWrite(stopper, 0);
  Serial.println("ocdi");
}

void initWifiStation() {
  delay(10);
  Serial.println('\n');
  wifiMulti.addAP("Smartcar", "Smartcar");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("Akylly_Ahal_1", "akylly_ahal_1");
  wifiMulti.addAP("ELECTRONICLAB", "Electronic123");
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  WiFi.hostname("Akylly Cyra");
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  server.begin();
  Serial.println("HTTP server started");
}

void initMQTTClient() {
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.println("Connecting to public emqx mqtt broker.....");
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      if (WiFi.status() != WL_CONNECTED) {
        initWifiStation();
      }
      delay(5000);
    }
  }
}
