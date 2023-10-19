#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define gassensor A0
#define high 500

const int led1 = 16; //d0
const int led2 = 4; //d1
const int led3 = 0; //d2
const int led4 = 5; //d3
const int led5 = 13; //d4
const int buzz = 2;

const int buzzer_gas = 13;

int pir_val = 0;
int ldr_val = 0;
int gas;

const char* ssid = "Test";
const char* password = "12345678";

ESP8266WebServer server(80);
void returnCheck() {
  server.send(200, "text/html", "Ishleyar" );
}
void led1on() {
  server.send(200, "text/html", "led_1_on");
  digitalWrite(led1, HIGH);
  Serial.println("s1_on");
}
void led2on() {
  server.send(200, "text/html", "led_2_on");
  digitalWrite(led2, HIGH);
  Serial.println("s2_on");
}
void led3on() {
  server.send(200, "text/html", "led_3_on");
  digitalWrite(led3, HIGH);
  Serial.println("s3_on");
}
void led4on() {
  server.send(200, "text/html", "led_4_on");
  tone(buzz, 1000, 3000); // B4
  Serial.println("s3_on");
}
void led5on() {
  gasss();
  pirrr();
  ldrrr();
}
void led1off() {
  server.send(200, "text/html", "led_1_off");
  digitalWrite(led1, LOW);
  Serial.println("s1_off");
}
void led2off() {
  server.send(200, "text/html", "led_2_off");
  digitalWrite(led2, LOW);
  Serial.println("s2_off");
}
void led3off() {
  server.send(200, "text/html", "led_3_off");
  digitalWrite(led3, LOW);
  Serial.println("s3_off");
}
void led4off() {
  server.send(200, "text/html", "led_4_off");
  tone(buzz, 1000, 3000); // B4
  Serial.println("s3_off");
}
void led5off() {
  loop();
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(buzz, LOW);
  pinMode(gassensor, INPUT);
  pinMode(buzzer_gas, OUTPUT);


  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  //    WiFi.config(staticIP , gateway, subnet, dns);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  server.begin();
  Serial.println("Server started");
  server.on("/check/", returnCheck);
  server.on("/led_1_on/", led1on);
  server.on("/led_2_on/", led2on);
  server.on("/led_3_on/", led3on);
  server.on("/led_4_on/", led4on);
  server.on("/led_5_on/", led5on);
  server.on("/led_1_off/", led1off);
  server.on("/led_2_off/", led2off);
  server.on("/led_3_off/", led3off);
  server.on("/led_4_off/", led4off);
  server.on("/led_5_off/", led5off);
}

void loop() {
  server.handleClient();
  pirrr();
  ldrrr();
//    gasss();
  //  server.handleClient();


}
void pirrr() {
  pir_val = digitalRead(12);
  Serial.println(pir_val);
  if (pir_val == 1) {
    tone(led4, 1000, 5000); // B4
  }
  else {
    noTone(led4); // B4
  }
}

void ldrrr() {
  ldr_val = digitalRead(14);
  Serial.println(ldr_val);
  if (ldr_val == 1) {
    digitalWrite(led5, HIGH);
  }
  else {
    digitalWrite(led5, LOW);
  }
}
void gasss() {
  
  Serial.println(gas);
  if (gas >= high) {
    tone(led4, 1000, 2000); // B4
  }
  else {
    noTone(led4); // B4
  }
}
