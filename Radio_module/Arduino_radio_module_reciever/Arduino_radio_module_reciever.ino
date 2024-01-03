#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

const int fr = 4;
const int fl = 5;
const int br = 6;
const int bl = 7;

void setup() {
  rf_driver.init();
  Serial.begin(9600);
  pinMode(fr, OUTPUT);
  pinMode(fl, OUTPUT);
  pinMode(br, OUTPUT);
  pinMode(bl, OUTPUT);

  digitalWrite(fr, LOW);
  digitalWrite(fl, LOW);
  digitalWrite(br, LOW);
  digitalWrite(bl, LOW);
}

void loop() {
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  if (rf_driver.recv(buf, &buflen)) {
    Serial.print("Message Received: ");
    Serial.println((char*)buf);

    if (buf[0] == '1') {
      Serial.println("One");
      digitalWrite(fr, HIGH);
      digitalWrite(fl, HIGH);
      digitalWrite(br, LOW);
      digitalWrite(bl, LOW);
    } else if (buf[0] == '2') {
      Serial.println("Yza");
      digitalWrite(fr, LOW);
      digitalWrite(fl, LOW);
      digitalWrite(br, HIGH);
      digitalWrite(bl, HIGH);
    } else if (buf[0] == '4') {
      Serial.println("Saga");
      digitalWrite(fr, HIGH);
      digitalWrite(fl, LOW);
      digitalWrite(br, LOW);
      digitalWrite(bl, HIGH);
    } else if (buf[0] == '3') {
      Serial.println("Chepe");
      digitalWrite(fr, LOW);
      digitalWrite(fl, HIGH);
      digitalWrite(br, HIGH);
      digitalWrite(bl, LOW);
    } else if (buf[0] == '5') {
      Serial.println("Stop");
      digitalWrite(fr, LOW);
      digitalWrite(fl, LOW);
      digitalWrite(br, LOW);
      digitalWrite(bl, LOW);
    }
  }
}
