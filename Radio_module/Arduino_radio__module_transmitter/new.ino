#include <RH_ASK.h>
#include <SPI.h>
#include <Servo.h>

RH_ASK rf_driver;
Servo myServo;

void setup() {
  Serial.begin(9600);   // Seri iletişim başlat
  if (!rf_driver.init())
    Serial.println("RH_ASK initialization failed");

  myServo.attach(9);    // Servo motoru 9. pine bağla
}

void loop() {
  // Gönderici (Transmitter) tarafı
  const char *message = "Hello, Servo!";
  rf_driver.send((uint8_t *)message, strlen(message));
  rf_driver.waitPacketSent();

  delay(1000);  // 1 saniye bekle

  // Alıcı (Receiver) tarafı
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (rf_driver.recv(buf, &buflen)) {
    buf[buflen] = '\0';
    Serial.print("Received: ");
    Serial.println((char*)buf);

    // Servo motoru hareket ettir
    if (strcmp((char*)buf, "Hello, Servo!") == 0) {
      myServo.write(90);  // Servo motoru 90 dereceye ayarla
      delay(1000);        // 1 saniye bekle
      myServo.write(0);   // Servo motoru 0 dereceye ayarla
    }
  }
}
