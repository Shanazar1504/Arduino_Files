#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>

#define RX_PIN 50
#define TX_PIN 51

SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX
DFRobotDFPlayerMini player;

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;

int currentVolume = 20; // Initial volume level

int pos = 90;    // variable to store the servo position
int pos1 = 90;    // variable to store the servo position
int pos2 = 90;    // variable to store the servo position

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

  if (!player.begin(mySerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }

  myservo1.attach(2);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(3);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(4);  // attaches the servo on pin 9 to the servo object
  myservo4.attach(5);  // attaches the servo on pin 9 to the servo object
  myservo5.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo6.attach(7);  // attaches the servo on pin 9 to the servo object


  stopServo();


  Serial.println(F("DFPlayer Mini online."));
}

void loop() {
  if (Serial.available()) {
    byte command = Serial.read();
    Serial.println(command);
    switch (command) {
      case 'P':
        player.play();
        action();
        break;
      case 'S':
        player.pause();
        stopServo();
        break;
      case 'U':
        player.volumeUp();
        currentVolume += 5; // Increase volume
        if (currentVolume > 30) currentVolume = 30; // Max volume
        break;
      case 'D':
        player.volumeDown();
        currentVolume -= 5; // Decrease volume
        if (currentVolume < 0) currentVolume = 0; // Min volume
        break;
      case 'N':
        player.next();
        break;
      case 'B':
        player.previous();
        break;
      case 'A':
        action();
        break;
      case 'R':
        stopServo();
        break;
      case 'M':
        playSpecificMP3(1); // Change 1 to the number of the MP3 file you want to play
        break;
    }
  }
}

void stopServo() {
  myservo1.write(90);
  myservo2.write(70);
  myservo3.write(70);
  myservo4.write(110);
  myservo5.write(120);
  myservo6.write(170);
}
void action() {

  for (pos = 110; pos >= 60; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 120; pos >= 60; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo5.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 170; pos >= 100; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo6.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 70; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 70; pos <= 150; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 110; pos >= 70; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 150; pos >= 70; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 70; pos <= 110; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 70; pos <= 150; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}

//00:22:09:01:80:DE


void playSpecificMP3(int mp3Number) {
  player.playMp3Folder(mp3Number);
  delay(100); // Delay to allow the MP3 to start playing
}
