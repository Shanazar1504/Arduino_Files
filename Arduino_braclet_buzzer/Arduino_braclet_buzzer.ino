#include <RH_ASK.h>

RH_ASK rf_driver;

const int buzzerPin = 7; // Adjust this to the actual pin connected to the buzzer


void setup() {
  rf_driver.init();
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

}


void loop() {
 uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (rf_driver.recv(buf, &buflen)) {
    // Message received, print it
    buf[buflen] = '\0';
    Serial.print("Message received: ");
    Serial.println((char*)buf);

    // Check if the received message is "K is equal to 10!"
    if (strcmp((char*)buf, "K is equal to 10!") == 0) {
      // Activate the buzzer
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
