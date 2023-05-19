#include <Wire.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

const int MPU_addr = 0x68; // I2C address of the MPU6050
int16_t GyX, GyY, GyZ; // variables to store accelerometer and gyroscope data
const int value1 = -5500;
const int value2 = 5500;
const int magnetic = 4;
int state = 0;
char *controller;

void setup() {
  Serial.begin(9600);
  pinMode(magnetic, INPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  mySwitch.enableTransmit(12);
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
  if (GyX <= value1)
  {
    mySwitch.send(5, 10);
    Serial.println("One");
  }
  else if (GyX >= value2) {
    mySwitch.send(4, 10);
    Serial.println("Yza");
  }
  else if (GyY <= value1) {
    mySwitch.send(3, 10);
    Serial.println("Chepe");
  }
  else if (GyY >= value2) {
    mySwitch.send(2, 10);
    Serial.println("Saga");
  }
  else if (digitalRead(magnetic) == 0) {
    mySwitch.send(0, 10);
    Serial.println("gys");
  }
  else if (digitalRead(magnetic) == 1) {
    mySwitch.send(1, 10);
    Serial.println("ach");
  }
  delay(100);
}
