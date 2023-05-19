#include <RCSwitch.h>
#include <Servo.h>

RCSwitch mySwitch = RCSwitch();

Servo motor_1;
Servo motor_2;
Servo motor_3;
Servo motor_4;

int servo1 = 90;
int servo2 = 90;
int servo3 = 98;
int servo4 = 90;


void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);

  motor_1.attach(11);
  motor_2.attach(10);
  motor_3.attach(9);
  motor_4.attach(8);

  motor_1.write(servo1);
  motor_2.write(servo2);
  motor_3.write(servo3);
  motor_4.write(servo4);

}
void loop() {
  if (mySwitch.available()) {
    Serial.println( mySwitch.getReceivedValue() );
    if (mySwitch.getReceivedValue() == 0) {
      if (servo1 < 90) {
        servo1 = servo1 + 5;
      }
      motor_1.write(servo1);

    }
    else if (mySwitch.getReceivedValue() == 1) {
      if (servo1 > 0) {
        servo1 = servo1 - 5;
      }
      motor_1.write(servo1);
    }
    else if (mySwitch.getReceivedValue() == 2) {
      if (servo2 < 180) {
        servo2 = servo2 + 5;
      }
      motor_2.write(servo2);

    }
    else if (mySwitch.getReceivedValue() == 3) {
      if (servo2 > 0) {
        servo2 = servo2 - 5;
      }
      motor_2.write(servo2);
    }
    else if (mySwitch.getReceivedValue() == 4) {
      if (servo3 < 180) {
        servo3 = servo3 + 5;
      }
      motor_3.write(servo3);

    }
    else if (mySwitch.getReceivedValue() == 5) {
      if (servo3 > 0) {
        servo3 = servo3 - 5;
      }
      motor_3.write(servo3);
    }

    mySwitch.resetAvailable();
  }
}
