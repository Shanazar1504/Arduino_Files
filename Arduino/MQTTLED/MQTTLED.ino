// Author : Mudassar Tamboli
// Date   : 6/8/2018

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>   

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char* mqttServer   = "192.168.0.102";
const int   mqttPort     = 1883;  
const char* mqttUser     = "";
const char* mqttPassword = "";

//#define PUB "car/gpio/status"
//#define SUB "car/gpio/action"
#define PUB "action"
#define SUB "device"

String received_payload;
int relay_state;
unsigned long previousMillis = 0;
unsigned long interval = 30000;


const int led_pin_1 = 14;

void setup() {
    Serial.begin(115200);

    
    server.on("/activate/", activate);
    server.on("/deactivate/", deactivate);
    
    pinMode(led_pin_1, OUTPUT);
  
    initWifiStation();
    initMQTTClient();
} 

void loop() {
    mqttClient.loop();
    server.handleClient();

    unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    initWifiStation();
    previousMillis = currentMillis;
  }
  
}


void activate() {
  mqttServer = "mqtt.flespi.io";
  
    initMQTTClient();
  server.send(200, "text/html", "activated");
  
}

void deactivate() {
  mqttServer = "192.168.1.101";
  
    initMQTTClient();
  server.send(200, "text/html", "deactivated");
}


 
void PubSubCallback(const MQTT::Publish && pub) {

  Serial.print(pub.topic());   // выводим в сериал порт название топика
  Serial.print(":");
  Serial.println(pub.payload_string()); // выводим в сериал порт значение полученных данных
  
  received_payload = pub.payload_string(); // сохраняем полученные данные
  
  if (String(pub.topic()) == SUB) { // если топик на который пришли данные, равен топику на который приходит состояние реле, то
    relay_state = received_payload.toInt(); // преобразуем полученные данные в тип integer

    if(relay_state == 1) {
        Serial.println("cyra yandy");
        digitalWrite(led_pin_1, 1);
        mqttClient.publish(PUB, "1");
        
    } else if(relay_state == 0) {
        Serial.println("cyra ocdi");
        digitalWrite(led_pin_1, 0);
        mqttClient.publish(PUB, "0");
    }
  }
}



//############### INIT WIFI STATION #####################//
void initWifiStation() {
    delay(10);
    Serial.println('\n');
    wifiMulti.addAP("Pip", "bionics123");   // add Wi-Fi networks you want to connect to
    wifiMulti.addAP("LDR", "12345678");
    wifiMulti.addAP("TP-LINK_BF4C", "1020304050");
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

//############### INIT MQTT CLIENT #####################//
void initMQTTClient() {
    mqttClient.set_server(mqttServer, mqttPort);
    mqttClient.set_callback(PubSubCallback);
    while (!mqttClient.connected()) {
        Serial.println(String("Connecting to MQTT (") + mqttServer + ")...");
        if (mqttClient.connect(MQTT::Connect("arduinoClient2")
         .set_auth(mqttUser, mqttPassword))) {
            Serial.println("MQTT client connected");    
        } else {
            Serial.print("\nFailed with state ");
//            Serial.println(mqttClient.state()); 
            if (WiFi.status() != WL_CONNECTED) {
               initWifiStation();
            }
            delay(5000);
        }
    }
    // Declare Pub/Sub topics
    mqttClient.publish(PUB, "active");
    mqttClient.subscribe(SUB);
}
