#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

uint8_t DHTPin = D8;

int LED = 2; // nodemcun oz cyrajygy 2 pin led dakmak hokman dall
// WiFi
const char *ssid = "TP-LINK_BF4C"; // Enter your WiFi name
const char *password = "1020304050";  // Enter WiFi password
// Enter WiFi password
// MQTT Broker
const char *mqtt_broker = "192.168.0.101";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

unsigned long previousMillis = 0;
unsigned long interval = 5000;

#define humidity_topic "humidity"
#define temperature_topic "temperature"

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  // connecting to a WiFi network
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
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
 publish and subscribe
    client.publish(topic, "dgffgjh");
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
    digitalWrite(LED, LOW);  // LED off
    Serial.println("LED OFF");
    client.publish(topic, "LED OFF");
  }
  if (message == "1") {
    digitalWrite(LED, HIGH); // LED ON
    Serial.println("LED ON");
    client.publish(topic, "LED ON");

  }
  Serial.println();
  Serial.println("---------------------- -");
}

float temp;
float hum;

void loop() {
  client.loop();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //read humidity and publish to android app
    hum = dht.readHumidity();
    Serial.print("New humidity:");
    Serial.println(String(hum).c_str());
    client.publish(humidity_topic, String(hum).c_str(), true);
    //read temperature and publish to android app
    temp = dht.readTemperature();
    Serial.print("New temperature:");
    Serial.println(String(temp).c_str());
    client.publish(temperature_topic, String(temp).c_str(), true);

  }
}
