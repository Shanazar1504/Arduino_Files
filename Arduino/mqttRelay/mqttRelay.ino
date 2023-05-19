#include <ESP8266WiFi.h> // подключаем библиотеку для работы с WiFi
#include <PubSubClient.h> // подключаем библиотеку для работы с MQTT
#include <EEPROM.h> // подключаем библиотеку для доступа к EEPROM памяти
#include <time.h> // подключаем библиотеку для того чтобы получать время из Интернета 
#include <Wire.h> // подключаем библиотеку "Wire"

#define relay_unlock_door 0 // пин к которому вы подключили реле 
#define relay_lock_door 1 
#define relay_ignition 2 
#define relay_engine 3 


#define unlock_door_topic "/car/status/unlockDoor/"    // имя топика на который будет приходить состояние реле
#define lock_door_topic "/car/status/lockDoor/"
//#define ignition_topic "/car/status/ignition/"
//#define engine_topic "/car/status/engine/"

const char *ssid_name      = "LDR";         // название вашей WiFi сети
const char *ssid_password  = "12345678"; // пароль указанной выше WiFi сети

const char *broker_address = "test.mosquitto.org"; // адресс MQTT сервера 
const int  server_port     = 1883;                   // порт сервера
const char *user_name      = "didar";                // имя пользователя
const char *user_password  = "12345";           // пароль пользователя

String received_payload; // переменная для хранения значения полученого от MQTT клиента 

int relay_state;    // переменная для хранения состояния реле


void MQTTCallbacks(const MQTT::Publish& pub) { // функция получения данных от MQTT клиента
  Serial.print(pub.topic());   // выводим в сериал порт название топика
  Serial.print(":");
  Serial.println(pub.payload_string()); // выводим в сериал порт значение полученных данных
  
  received_payload = pub.payload_string(); // сохраняем полученные данные
  
  if (String(pub.topic()) == unlock_door_topic) { // если топик на который пришли данные, равен топику на который приходит состояние реле, то
    relay_state = received_payload.toInt(); // преобразуем полученные данные в тип integer
   
    if(relay_state == 1) {
      digitalWrite(relay_unlock_door, HIGH);  //  включаем или выключаем светодиод в зависимоти от полученных значений данных
      delay(100);
      digitalWrite(relay_unlock_door, LOW);
      Serial.println("Unlock door"); 
    }
  }

    
  if (String(pub.topic()) == lock_door_topic) { 
    relay_state = received_payload.toInt(); 
  
    if(relay_state == 1) {
      digitalWrite(relay_lock_door, HIGH); 
      delay(100);
      digitalWrite(relay_lock_door, LOW);
      Serial.println("Lock door"); 
    }
  }

    
  if (String(pub.topic()) == ignition_topic) { 
    relay_state = received_payload.toInt(); 
  
    if(relay_state == 1) {
      digitalWrite(relay_ignition, HIGH); 
      Serial.println("Ignition switch ON"); 
    } else {
      digitalWrite(relay_ignition, LOW);
      Serial.println("Ignition switch OFF"); 
    }
  }


    if (String(pub.topic()) == engine_topic) { 
    relay_state = received_payload.toInt(); 
  
    if(relay_state == 1) {
      digitalWrite(relay_engine, HIGH); 
      delay(1500);
      digitalWrite(relay_engine, LOW);
      Serial.println("Engine start"); 
    }
  }
  
}

WiFiClient wifi_client; // создаём объект обозначающий WiFi клиент  
PubSubClient client(wifi_client, broker_address, server_port); // создаём объект обозначающий MQTT клиент

void setup() {
  Serial.begin(115200); // указываем скорость работы COM порта
  pinMode(relay_unlock_door, OUTPUT); // настраиваем пин к которому подключено реле как выход
  pinMode(relay_lock_door, OUTPUT);
  pinMode(relay_ignition, OUTPUT);
  pinMode(relay_engine, OUTPUT);
  
  digitalWrite(relay_unlock_door, LOW); // выключаем реле
  digitalWrite(relay_lock_door, LOW);
  digitalWrite(relay_ignition, LOW);
  digitalWrite(relay_engine, LOW);

}


void loop() {
  if (WiFi.status() != WL_CONNECTED) { // если плата ESP8266 не подключена к WiFi, то
    Serial.print("Подключаемся к WiFi точке: ");
    Serial.println(ssid_name);
    WiFi.begin(ssid_name, ssid_password); // подключаемся к WiFi используя указаные вами название WiFi точки и её пароль

    if (WiFi.waitForConnectResult() != WL_CONNECTED) // если плата ESP8266 подключается к WiFi, то
      return;
    Serial.println("Подключились к WiFi!");
    Serial.print("Локальный IP платы ESP8266: ");
    Serial.println(WiFi.localIP()); // получаем и выводим IP платы ESP8266


    Serial.println("Время отклика ... OK");
  }

  // подключаемся к MQTT серверу
  if (WiFi.status() == WL_CONNECTED) { // если плата ESP8266 подключена к WiFi
    if (!client.connected()) { // если плата ESP8266 не подключена к MQTT серверу
      Serial.println("Подключаемся к MQTT серверу ...");
      if (client.connect(MQTT::Connect("arduinoClient2")
         .set_auth(user_name, user_password))) { // авторизируемся на MQTT сервере
        Serial.println("Подключились к MQTT серверу!");
        client.set_callback(MQTTCallbacks); // указываем функцию получения данных от MQTT клиента
        // подписываемся на топики, которые вы указали
        client.subscribe(unlock_door_topic);
        client.subscribe(lock_door_topic);
        client.subscribe(ignition_topic);
        client.subscribe(engine_topic);
      } else {
        Serial.println("Не удалось подключиться к MQTT серверу :(");
      }
    }

    if (client.connected()) { // если плата ESP8266 подключена к MQTT серверу
      client.loop();
      // отправка данных на топики, на которые подписана плата ESP8266

    }
  }
}
