/* This code for MeArm robot using joystick shield with arduino uno
   Please use orginal arduino uno
   I use power adaptor 12v
   Don't forget to adjust the servo position in 0 degree or 180 degree when attaching the servo horn
   Make sure the linkages are smooth, you can enlarge diameter
*/

#include <Servo.h>
Servo servo_x;  // create servo object to control a servo
Servo servo_y;  // create servo object to control a servo
Servo servo_z;  // create servo object to control a servo
Servo servo_grip;  // create servo object to control a servo

// Declare the pins for the Button
int x_pin = A0;
int y_pin = A1;
int z_pin = A2;
int grip_pin = A3;

int x_pos;    // variable to store the servo position
int y_pos;    // variable to store the servo position
int z_pos;    // variable to store the servo position
int grip_pos;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  // Define pin as input and activate the internal pull-up resistor
  //setup servo
  servo_x.attach(11);  // attaches the servo x
  servo_y.attach(10);  // attaches the servo y
  servo_z.attach(9);  // attaches the servo z
  servo_grip.attach(5);  // attaches the servo grip

  //origin position
  x_pos = 90;
  y_pos = 0;
  z_pos = 175;
  grip_pos = 0;

  servo_x.write(x_pos);
  servo_y.write(y_pos);
  servo_z.write(z_pos);
  servo_grip.write(grip_pos);
}

void loop() {
  // Read the value of the input
  int val_x = analogRead(x_pin);
  int val_y = analogRead(y_pin);
  int val_z = analogRead(z_pin);
  int val_grip = analogRead(grip_pin);

  delay(15);
  // joystick X========================================
  if (val_x < 400) {
    if (x_pos < 180) {
      x_pos = x_pos + 1;
      servo_x.write(x_pos);
    }
  }
  else if (val_x > 750) {
    if (x_pos > 0) {
      x_pos = x_pos - 1;
      servo_x.write(x_pos);
    }
  }
  // joystick X========================================

  // joystick Y========================================
  if (val_y < 400) {
    if (y_pos < 120) {
      y_pos = y_pos + 1;
      servo_y.write(y_pos);
    }
  }
  else if (val_y > 750) {
    if (y_pos > 0) {
      y_pos = y_pos - 1;
      servo_y.write(y_pos);

      //check z pos
      if (z_pos < 150)
      {
        if (z_pos < 175) {
          z_pos = z_pos + 1;
          servo_z.write(z_pos);
        }
      }
    }
  }
  // joystick Y========================================

  // joystick Z========================================
  if (val_z < 400) {
    if (z_pos < 175) {
      z_pos = z_pos + 1;
      servo_z.write(z_pos);
    }
  }
  else if (val_z > 750 && y_pos > 40) {
    if (z_pos > 90) {
      z_pos = z_pos - 1;
      servo_z.write(z_pos);
    }
  }
  // joystick Z========================================

  // joystick grip========================================
  if (val_grip < 400) {
    if (grip_pos < 30) {
      grip_pos = grip_pos + 1;
      servo_grip.write(grip_pos);
    }
  }
  else if (val_grip > 750) {
    if (grip_pos > 0) {
      grip_pos = grip_pos - 1;
      servo_grip.write(grip_pos);
    }
  }
  // joystick grip========================================

  Serial.print("x_axis: ");
  Serial.print(x_pos);
  Serial.print(", y_axis: ");
  Serial.print(y_pos);
  Serial.print(", z_axis: ");
  Serial.println(z_pos);
}
