#include <SoftwareSerial.h>
#include <Servo.h>

Servo gysyan;
SoftwareSerial bluetoothSerial(10, 11); // RX, TX pinleri

void setup() {
  gysyan.attach(2);
  Serial.begin(9600); // Seri monitör için baud hızı
  bluetoothSerial.begin(9600); // Bluetooth modülü için baud hızı

  Serial.println("Bluetooth veri alimi baslatildi. Lutfen baglanti yapin.");
}

void loop() {
  // Bluetooth modülünden gelen veriyi kontrol et
  if (bluetoothSerial.available() > 0) {
    char receivedChar = bluetoothSerial.read();
    Serial.print(receivedChar); // Seri monitöre yazdır

    if (receivedChar == 'F') {
      gysyan.write(180);
      Serial.write("HI");
    }

    if (receivedChar == 'f') {
      gysyan.write(110);
    }
  }
}
