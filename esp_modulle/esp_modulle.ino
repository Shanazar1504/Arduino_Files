#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "ELECTRONICLAB";
const char *password = "Electronic123";

const char *mqtt_broker = "192.168.0.102";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;
const char *topic = "device";
const char *scale_topic = "scale";
const char *body_topic = "body";
const char *heart_topic = "heart";
const char *hum_topic = "hum";
const char *temp_topic = "temp";

String stream;
String sensorData[5];
int arrIndex = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  //  client.setCallback(callback);
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
  client.publish(topic, "Baglandy");
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
    Serial.println("LED OFF");
  }
  if (message == "1") {
    Serial.println("LED ON");
  }
  Serial.println();
  Serial.println("---------------------- -");
}
void loop() {
  client.loop();
  if (Serial.available() != 0) {
    for (int i = 0; i < 5; i++) {
      sensorData[i] = Serial.readStringUntil('\n');
    }
    Serial.println('\t');
    Serial.print(sensorData[0]);
    Serial.println('\t');
    Serial.print(sensorData[1]);
    Serial.print('\t');
    Serial.print(sensorData[2]);
    Serial.print('\t');
    Serial.print(sensorData[3]);
    Serial.print('\t');
    Serial.println(sensorData[4]);
  }
  client.publish(hum_topic, String(sensorData[0]).c_str(), true);
  client.publish(temp_topic, String(sensorData[1]).c_str(), true);
  client.publish(body_topic, String(sensorData[2]).c_str(), true);
  client.publish(heart_topic, String(sensorData[3]).c_str(), true);
  client.publish(scale_topic, String(sensorData[4]).c_str(), true);
}
