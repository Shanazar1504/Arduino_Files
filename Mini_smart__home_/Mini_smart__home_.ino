#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11

#define pirPin 13
int PIRValue = 0;

const int led1 = 4;
const int led2 = 0;
const int buzzer = 12;

#define gassensor A0
#define high 600

const char *ssid = "Pip";
const char *password = "bionics123";

const char *mqtt_broker = "192.168.43.1";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const char *topic = "device";
const char *hum_topic = "hum";
const char *temp_topic = "temp";
const char *gas_topic = "gas";
const char *mot_topic = "mot";

unsigned long previousMillis = 0;
unsigned long interval = 2000;
String stream;
String message;

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(buzzer, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(gassensor, INPUT);
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
      delay(500);
    }
  }
  //   publish and subscribe
  //  client.publish(topic, "Baglandy");
  client.subscribe(topic);

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
  if (message == "2") {
    led1off();
  }
  else if (message == "1") {
    led1on();
  }
  else if (message == "4") {
    led2off();
  }
  else if (message == "3") {
    led2on();
  }
}

float temp;
float hum;


void loop() {
  client.loop();
  dhtt();
  PIRSensor();
  gasss();
  delay(500);
}
void dhtt() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //read humidity and publish to android app
    hum = dht.readHumidity();
    client.publish(hum_topic, String(hum).c_str(), true);
    //read temperature and publish to android app
    temp = dht.readTemperature();
    client.publish(temp_topic, String(temp).c_str(), true);
  }
}
void led1off() {
  digitalWrite(led1, 0);
  Serial.println("ochdi");
}
void led1on() {
  digitalWrite(led1, 1);
  Serial.println("yandy");
}
void led2off() {
  digitalWrite(led2, 0);
  Serial.println("ochdi");
}
void led2on() {
  digitalWrite(led2, 1);
  Serial.println("yandy");
}
void PIRSensor() {
  if (digitalRead(pirPin) == HIGH) {
    PIRValue = 1;
    client.publish(mot_topic, String(PIRValue).c_str(), true);
     tone(buzzer, 1000, 500);
    delay(50);
  }
  else {
    PIRValue = 0;
    client.publish(mot_topic, String(PIRValue).c_str(), true);
    noTone(buzzer);

  }
  delay(500);
}
void gasss() {
  int gas_value = analogRead(gassensor);
  Serial.println(gas_value);
  client.publish(gas_topic, String(gas_value).c_str(), true);
  if (gas_value > high) {
     tone(buzzer, 1000, 500);
  }
  else {
noTone(buzzer);
  }
    delay(500);
}
