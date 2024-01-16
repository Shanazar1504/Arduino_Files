#include <VirtualWire.h>
#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(9);  // Servo signal pin

  vw_set_ptt_inverted(true);
  vw_setup(2000);  // Bits per sec
  vw_rx_start();
}

void loop() {
  uint8_t buf[sizeof(int)];
  uint8_t buflen = sizeof(buf);

  if (vw_get_message(buf, &buflen)) {
    int receivedValue;
    memcpy(&receivedValue, buf, sizeof(receivedValue));

    // Map the received value to servo angle (adjust as needed)
    int servoAngle = map(receivedValue, 0, 1023, 0, 180);
    myservo.write(servoAngle);
  }
}
