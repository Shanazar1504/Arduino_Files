#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Arduino.h>
#include "HX711.h"

#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22


const int led = 4;
long randNumber;

const char *ssid = "Pip";
const char *password = "bionics123";

const char *mqtt_broker = "192.168.43.1";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *topic = "device";
const char *scale_topic = "scale";
const char *body_topic = "body";
const char *heart_topic = "heart";
const char *hum_topic = "hum";
const char *temp_topic = "temp";

unsigned long previousMillis = 0;
unsigned long interval = 1000;
String serialData;
String stream;
String sensorData[2];
int arrIndex = 0;
String agram;

const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 14;

HX711 scale;

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  dht.begin();

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
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
      delay(2000);
    }
  }
  //   publish and subscribe
  //  client.publish(topic, "Baglandy");
  client.subscribe(topic);

  scale.set_scale(393.254);
  scale.tare();
}

void callback(char *topic, byte *payload, unsigned int length) {
  //  Serial.print("Message arrived in topic: ");
  //  Serial.println(topic);
  //  Serial.print("Message:");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char) payload[i];
    // convert *byte to string
  }
  if (message == "0") {
    Serial.println("Reconnecting to WiFi...");
    digitalWrite(led, 0);
  }
  else if (message == "1") {
    digitalWrite(led, 1);
  }
}

float temp;
float hum;

void loop() {

    randNumber = random(10, 20);
  Serial.println(randNumber);
  client.loop();
  if (Serial.available() != 0) {
    serialData = Serial.readStringUntil('\n');
  }

  for (int i = 0; i < serialData.length(); i++) {
    if (serialData[i] == '+') {
      sensorData[0] = serialData.substring(0, i);
      sensorData[1] = serialData.substring(i + 1, serialData.length());
    }
  }

  state2();
  state4();
  state1();
  state3();
  sendStates();
}

void state1() {
  Serial.println(sensorData[0]);
}
void state2() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //read humidity and publish to android app
    hum = dht.readHumidity();
    Serial.print("New humidity:");
    Serial.println(String(hum).c_str());
    client.publish(hum_topic, String(hum).c_str(), true);
    //read temperature and publish to android app
    temp = dht.readTemperature();
    Serial.print("New temperature:");
    Serial.println(String(temp).c_str());
    client.publish(temp_topic, String(temp).c_str(), true);
  }
}

void sendStates() {
  client.publish(body_topic, String(sensorData[0]).c_str(), true);
  client.publish(heart_topic, String(sensorData[1]).c_str(), true);
}

void state3() {
  Serial.println(sensorData[1]);
}
void state4() {
  if (0 < scale.get_units() && scale.get_units() < 15) {
    agram = "0";
  };
  if (15 < scale.get_units() && scale.get_units() < 50) {
    agram = "1";
  };
  if (50 < scale.get_units() && scale.get_units() < 100) {
    agram = "2";
  };
  if (100 < scale.get_units() && scale.get_units() < 150) {
    agram = "3";
  };
  if (150 < scale.get_units() && scale.get_units() < 200) {
    agram = "4";
  };
  if (200 < scale.get_units() && scale.get_units() < 250) {
    agram = "5";
  };
  if (250 < scale.get_units() && scale.get_units() < 300) {
    agram = "6";
  };
  if (300 < scale.get_units() && scale.get_units() < 350) {
    agram = "7";
  };
  if (350 < scale.get_units() && scale.get_units() < 400) {
    agram = "8";
  };
  if (400 < scale.get_units() && scale.get_units() < 450) {
    agram = "9";
  };
  if (450 < scale.get_units() && scale.get_units() < 550) {
    agram = "10";
  };

  client.publish(scale_topic, String(agram).c_str(), true);

  scale.power_down();             // put the ADC in sleep mode
  delay(2000);
  scale.power_up();
}
