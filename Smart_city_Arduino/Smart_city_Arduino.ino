#include <SoftwareSerial.h>

SoftwareSerial master (2, 3);
String command;
String message1 = "Suw agdy1";
String message2 = "Suw agdy2";

const int led1 = 4;
const int led2 = 5;
const int led3 = 6;
const int led4 = 7;
const int led_all = 8;
const int street = A1;
const int pump = 10;
const int ldr = 11;
const int sensor1 = 12;
const int sensor2 = 13;

int ldr_val = 0;
int sen_val1 = 0;
int sen_val2 = 0;

void setup() {
  Serial.begin(9600);
  master.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led_all, OUTPUT);
  pinMode(street, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
}

void loop() {
  ldr_val = digitalRead(ldr);
  sen_val1 = digitalRead(sensor1);
  sen_val2 = digitalRead(sensor2);

  Serial.println(sen_val1);

  if (master.available()) {
    command = master.readStringUntil('\n');
    command.trim();
    if (command.length() > 0) {
      if (command == "led1_on") {
        digitalWrite(led1, HIGH);
      }
      else if (command == "led1_off") {
        digitalWrite(led1, LOW);
      }
      else if (command == "led2_on") {
        digitalWrite(led2, HIGH);
      }
      else if (command == "led2_off") {
        digitalWrite(led2, LOW);
      }
      else if (command == "led3_on") {
        digitalWrite(led3, HIGH);
      }
      else if (command == "led3_off") {
        digitalWrite(led3, LOW);
      }
      else if (command == "led4_on") {
        digitalWrite(led4, HIGH);
      }
      else if (command == "led4_off") {
        digitalWrite(led4, LOW);
      }
      else if (command == "led_all_on") {
        ledd_all_on();
      }
      else if (command == "led_all_off") {
        ledd_all_off();
      }
      //      else if (command == "light_on") {
      //        digitalWrite(street, HIGH);
      //      }
      //      else if (command == "light_off") {
      //        digitalWrite(street, LOW);
      //      }
      else if (command == "water_on") {
        digitalWrite(pump, HIGH);
      }
      else if (command == "water_off") {
        digitalWrite(pump, LOW);
      }
      Serial.println(command);
      command = "";
    }
  } else if (ldr_val == 1) {
    digitalWrite(street, HIGH);
  } else if (ldr_val == 0) {
    digitalWrite(street, LOW);
  }
  else if (sen_val1 == 1) {
    Serial.println("suww");
  }
  else if (sen_val2 == 1) {
    Serial.println(message2);
  }
}

void ledd_all_on() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led_all, HIGH);
}
void ledd_all_off() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led_all, LOW);
}
