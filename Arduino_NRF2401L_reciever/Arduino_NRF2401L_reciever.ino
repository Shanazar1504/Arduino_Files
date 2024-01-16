#include <Servo.h>
#include <RF24.h>

Servo motor_1;
Servo motor_2;
Servo motor_3;
Servo motor_4;
Servo motor_5;

RF24 radio(9, 10);  // CE, CSN pins on the NRF24L01 module

int servo1 = 90;
int servo2 = 90;
int servo3 = 90;
int servo4 = 90;
int servo5 = 90;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);  // Set the address for communication
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();

  motor_1.attach(8);
  motor_2.attach(9);
  motor_3.attach(10);
  motor_4.attach(11);
  motor_5.attach(12);

  motor_1.write(servo1);
  motor_2.write(servo2);
  motor_3.write(servo3);
  motor_4.write(servo4);
  motor_5.write(servo5);
}

void loop() {
  if (radio.available()) {
    int command;
    radio.read(&command, sizeof(command));
    Serial.println(command);

    if (command == 4) {
      if (servo1 < 180) {
        servo1 += 5;
      }
      motor_1.write(servo1);
    } else if (command == 5) {
      if (servo1 > 0) {
        servo1 -= 5;
      }
      motor_1.write(servo1);
    } else if (command == 3) {
      if (servo2 < 170 && servo3 < 135 && servo4 < 135) {
        servo2 += 5;
        servo3 += 3;
        servo4 += 3;
      }
      motor_2.write(servo2);
      motor_3.write(servo3);
      motor_4.write(servo4);
    } else if (command == 2) {
      if (servo2 > 10 && servo3 > 45 && servo4 > 45) {
        servo2 -= 5;
        servo3 -= 3;
        servo4 -= 3;
      }
      motor_2.write(servo2);
      motor_3.write(servo3);
      motor_4.write(servo4);
    } else if (command == 6) {
      if (servo5 < 150) {
        servo5 += 3;
      }
      motor_5.write(servo5);
    } else if (command == 7) {
      if (servo5 > 60) {
        servo5 -= 3;
      }
      motor_5.write(servo5);
    }
  }
}
