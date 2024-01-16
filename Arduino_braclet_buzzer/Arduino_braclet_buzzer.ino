#include <RH_ASK.h>

RH_ASK rf_driver;

const int buzzerPin = 7; // Adjust this to the actual pin connected to the buzzer


void setup() {
  rf_driver.init();
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

}


void loop() {
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  if (rf_driver.recv(buf, &buflen)) {
    Serial.print("Message Received: ");
    Serial.println((char*)buf);

    if (buf[0] == '1') {
      buzzerToneFunction();

    } else {
      digitalWrite(buzzerPin, LOW);
    }
  }
}

void buzzerToneFunction() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(200); // Adjust the duration of the buzzer sound
    digitalWrite(buzzerPin, LOW);
    delay(200); // Adjust the duration of the pause between buzzes
  }
}
