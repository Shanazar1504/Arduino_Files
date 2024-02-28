#include <SoftwareSerial.h>
#include <Servo.h>

//Servo gysyan;
//Servo asaky_servo;
  Servo hereket;
SoftwareSerial bluetoothSerial(10, 11); // RX, TX pinleri
int asagy ; 

int pos = 60;


void setup() {
  hereket.attach(2);
  //gysyan.attach(4);
  //asaky_servo.attach(3);
  Serial.begin(9600);           // Seri monitör için baud hızı
  bluetoothSerial.begin(9600);  // Bluetooth modülü için baud hızı

  Serial.println("Bluetooth veri alimi baslatildi. Lutfen baglanti yapin.");
}

void loop() {
  asagy = 90;
  // Bluetooth modülünden gelen veriyi kontrol et
  if (bluetoothSerial.available() > 0) {
    char receivedChar = bluetoothSerial.read();
    Serial.print(receivedChar); // Seri monitöre yazdır







    if (receivedChar == 'F') {
      pos -=10;
          pos = constrain(pos, 30, 150);
      hereket.write(pos);
    }


    if (receivedChar == 'B') {
         pos +=10;
          pos = constrain(pos, 0, 110);   
      hereket.write(pos);
    }


//
//    if (receivedChar == '1') {
//      Serial.println("ok");
//      asaky_servo.write(90);
//    }





//
//    if (receivedChar == 'H') {
//      Serial.println("ok");
//      gysyan.write(175);
//    }

//
//  if (receivedChar == 'L') {
//      gysyan.write(90);
//    }
//


//
//    if (receivedChar == 'R') {
//     
//        asaky_servo.write(160);
//        
//      
//    }
//
//
//     if (receivedChar == 'L') {
//     
//        asaky_servo.write(30);
//        
//      
//    }


    















    
  }
}
