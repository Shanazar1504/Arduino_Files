#include <Wire.h>
#include <VirtualWire.h>

const int MPU_addr = 0x68; // I2C address of the MPU6050
int16_t GyX, GyY, GyZ; // variables to store accelerometer and gyroscope data
const int value1 = -5500;
const int value2 = 5500;
const int magnetic = 4;
int state = 0;
char *controller;

void setup() {
  Serial.begin(115200);
  pinMode(magnetic, INPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  vw_set_ptt_inverted(true); //
  vw_set_tx_pin(12);
  vw_setup(4000);// speed of data transfer Kbps
  delay(100);
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  if (GyX <= value1) {
    controller = "5" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println("One");
    Serial.println(controller);
  } else if (GyX >= value2) {
    controller = "4" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println("Yza");
    Serial.println(controller);
  }  else if (GyY <= value1) {
    controller = "3" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println("Chepe");
    Serial.println(controller);
  }  else if (GyY >= value2) {
    controller = "2" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println("Saga");
    Serial.println(controller);
  } else if (digitalRead(magnetic) == 0) {
    controller = "1" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println("gys");
    Serial.println(controller);
  } else if (digitalRead(magnetic) == 1) {
    controller = "0" ;
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println("ach");
    Serial.println(controller);
  }
  delay(100);
}
