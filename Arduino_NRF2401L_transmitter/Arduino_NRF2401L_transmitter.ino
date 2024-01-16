#include <Wire.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins on the NRF24L01 module

const int MPU_addr = 0x68;
int16_t GyX, GyY, GyZ;
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
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL); // Set the address for communication
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();

  delay(100);
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);

  if (GyX <= value1) {
    sendData(1);
    Serial.println("One");
  } else if (GyX >= value2) {
    sendData(2);
    Serial.println("Yza");
  } else if (GyY <= value1) {
    sendData(3);
    Serial.println("Chepe");
  } else if (GyY >= value2) {
    sendData(4);
    Serial.println("Saga");
  } else {
    sendData(5);
    Serial.println("stop");
  }

  delay(100);
}

void sendData(int command) {
  radio.write(&command, sizeof(command));
}
