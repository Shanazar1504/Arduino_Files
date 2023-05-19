#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int fan_1 = 5;
int fan_2 = 4;
int fan_3 = 0;
int manual = 2;

// WiFi
const char *ssid = "TP-LINK_BF4C"; // Enter your WiFi name
const char *password = "1020304050";  // Enter WiFi password
// Enter WiFi password
// MQTT Broker
const char *mqtt_broker = "192.168.0.104";
const char *topic = "fan";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

#define PUB_GPIO_STATUS "status"
#define SUB_GPIO_ACTION "action"

WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network

  pinMode(fan_1, OUTPUT);
  pinMode(fan_2, OUTPUT);
  pinMode(fan_3, OUTPUT);
  pinMode(manual, OUTPUT);


  digitalWrite(fan_1, LOW);
  digitalWrite(fan_2, LOW);
  digitalWrite(fan_3, LOW);
  digitalWrite(manual, HIGH);


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
  // publish and subscribe
  client.publish(topic, "MQTT STARTED...");
  client.subscribe(topic);
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
  Serial.print(message);
  if (message == "0") {
    digitalWrite(fan_1, HIGH);
    digitalWrite(fan_2, LOW);
    digitalWrite(fan_3, LOW);
    digitalWrite(manual, LOW);
    Serial.println("fan_1");
    client.publish(PUB_GPIO_STATUS, "101");
    //client.publish(topic, "fan_1");
  }
  if (message == "1") {
    digitalWrite(fan_2, HIGH);
    digitalWrite(fan_1, LOW);
    digitalWrite(fan_3, LOW);
    digitalWrite(manual, LOW);
    Serial.println("fan_2");
    client.publish(topic, "fan_2");

  }
  if (message == "2") {
    digitalWrite(fan_3, HIGH);
    digitalWrite(fan_2, LOW);
    digitalWrite(fan_1, LOW);
    digitalWrite(manual, LOW);
    Serial.println("fan_3 ");
    client.publish(topic, "fan_3");
  }
  if (message == "3") {
    digitalWrite(manual, HIGH);
    digitalWrite(fan_2, LOW);
    digitalWrite(fan_3, LOW);
    digitalWrite(fan_1, LOW);
    Serial.println("manual");
    client.publish(topic, "manual");
  }
  Serial.println();
  Serial.println("---------------------- -");
}
void loop() {
  client.loop();
}
