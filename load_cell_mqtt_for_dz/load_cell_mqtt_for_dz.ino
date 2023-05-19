#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Arduino.h>
#include "HX711.h"


const char *ssid = "Test";
const char *password = "12345678";

const char *mqtt_broker = "192.168.43.1";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *topic = "device";
const char *scale_topic = "scale";
const char *heart_topic = "heart";
const char *sms_topic = "smss";

String agram = "sms";

long randNumber;

const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

const int buzzer = 5;

HX711 scale;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, 0);

  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
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

  client.subscribe(topic);

  scale.set_scale(729.414);
  scale.tare();
}

void loop() {
  client.loop();
  state3();
  state4();
}

void state3() {
  randNumber = random(70, 96);
  Serial.println(randNumber);
  client.publish(heart_topic, String(randNumber).c_str(), true);
  delay(10000);
}

void state4() {
  if (0 < scale.get_units()) {
    if (49 < scale.get_units() && scale.get_units() < 50) {
      last();
    }
    Serial.println(scale.get_units());
    client.publish(scale_topic, String(scale.get_units()).c_str(), true);
  }

  scale.power_down();             // put the ADC in sleep mode
  delay(2000);
  scale.power_up();
}
void last() {
  client.publish(sms_topic, String(agram).c_str(), true);
  digitalWrite(buzzer, 1);
  delay(1000);
  digitalWrite(buzzer, 0);
  delay(1000);
  digitalWrite(buzzer, 1);
  delay(1000);
  digitalWrite(buzzer, 0);
}
