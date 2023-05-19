#include <Servo.h>
#include <VirtualWire.h>
#define SERVO_PIN 9
#define RF_DATA_PIN 12
//Servo myservo;
void setup() {
//  myservo.attach(SERVO_PIN);
  vw_setup(2000); // Choose the appropriate baud rate for your RF module
  vw_set_rx_pin(RF_DATA_PIN);
  vw_rx_start();
  Serial.begin(9600); // Optional: for debugging
}
void loop() {
  if (vw_have_message()) {
    byte message[VW_MAX_MESSAGE_LEN];
    byte messageLength = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(message, &messageLength)) {
      int angle = map(message[0], 0, 255, 0, 180); // Map the received value to servo angle (0-180)
//      myservo.write(angle); // Set the servo position
      Serial.print("Received angle: ");
      Serial.println(angle); // Optional: for debugging
    }
  }
}
