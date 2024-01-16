// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>
#include <Wire.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

const int MPU_addr = 0x68; // I2C address of the MPU6050
int16_t GyX, GyY, GyZ; // variables to store accelerometer and gyroscope data
const int value1 = -5500;
const int value2 = 5500;
const int magnetic = 4;
int statee = 0;
char *controller;

void setup()
{
  Serial.begin(9600);
  pinMode(magnetic, INPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  rf_driver.init();
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  statee = digitalRead(magnetic);
  Serial.println(statee);
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);

  if (statee == 1) {
    const char *msg = "O";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("Open");
  }
  else if (GyX <= value1)
  {
    const char *msg = "A";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("One");
  }
  else if (GyX >= value2) {
    const char *msg = "B";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("Yza");
  }
  else if (GyY <= value1) {
    const char *msg = "C";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("Chepe");
  }
  else if (GyY >= value2) {
    const char *msg = "D";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("Saga");
  }
  else {
    const char *msg = "E";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("stop");
  }
}
