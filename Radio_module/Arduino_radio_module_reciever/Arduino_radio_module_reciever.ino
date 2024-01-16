#include <RH_ASK.h>
#include <SPI.h>
#include <Servo.h>

RH_ASK rf_driver;
ServoTimer2 myServo;

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

  myServo.attach(8);  // Use the appropriate pin for your servo
  myServo.write(90);  // Set the initial position of the servo

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

    if (buf[0] == 'A') {
      Serial.println("One");
      digitalWrite(fr, HIGH);
      digitalWrite(fl, HIGH);
      digitalWrite(br, LOW);
      digitalWrite(bl, LOW);
      myServo.write(0);  // Adjust the angle for your specific setup
    } else if (buf[0] == 'B') {
      Serial.println("Yza");
      digitalWrite(fr, LOW);
      digitalWrite(fl, LOW);
      digitalWrite(br, HIGH);
      digitalWrite(bl, HIGH);
      myServo.write(90);  // Adjust the angle for your specific setup
    } else if (buf[0] == 'C') {
      Serial.println("Saga");
      digitalWrite(fr, HIGH);
      digitalWrite(fl, LOW);
      digitalWrite(br, LOW);
      digitalWrite(bl, HIGH);
      myServo.write(180);  // Adjust the angle for your specific setup
    } else if (buf[0] == 'D') {
      Serial.println("Chepe");
      digitalWrite(fr, LOW);
      digitalWrite(fl, HIGH);
      digitalWrite(br, HIGH);
      digitalWrite(bl, LOW);
      myServo.write(90);  // Adjust the angle for your specific setup
    } else if (buf[0] == 'E') {
      Serial.println("Stop");
      digitalWrite(fr, LOW);
      digitalWrite(fl, LOW);
      digitalWrite(br, LOW);
      digitalWrite(bl, HIGH);
      myServo.write(90);  // Adjust the angle for your specific setup
    }
  }
}
