#include <SoftwareSerial.h>
#include "dht.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#define SD_ChipSelectPin 4

TMRpcm saz;

#define dht_pin A0 // Pin sensor is connected to
#define MIN_PULSE_WIDTH  650
#define MAX_PULSE_WIDTH  2350
#define DEFAULT_PULSE_WIDTH  1500
#define FREQUENCY 50


dht DHT;
SoftwareSerial BT(2, 3); // RX, TX
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int led = 7;

int state;

int temp;
int hum;

int pos = 0;

int timer = 0;

int prev = 0;

void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  BT.begin(9600); // Default communication rate of the Bluetooth module
  delay(500);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  saz.speakerPin = 9;
  Serial.begin(115200);
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
  saz.setVolume(5);
  saz.play("1.wav");

  digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);

  pwm.setPWM(0, 0, pulseWidth(180));
  pwm.setPWM(1, 0, pulseWidth(0));
  pwm.setPWM(2, 0, pulseWidth(90));
  pwm.setPWM(3, 0, pulseWidth(90));

}
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0 , 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int (float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}
void loop() {
  if (BT.available() > 0) {
    state = BT.read();
    Serial.println(state);
    if (state > 10) {
    }
  }

  timer = timer + 1;

  if (timer > 400) {
    DHT.read11(dht_pin);
    hum = DHT.humidity;
    temp = DHT.temperature;

    BT.print(temp);        //send distance to MIT App
    BT.print(";");
    BT.print(hum);         //send distance to MIT App
    BT.print(";");
    timer = 0;
  }

  if (state == 100 ) {
    salam();
  }
  else if (state == 101) {
    hello();
  }
  else if (state == 102) {
    adym();
  }
  else if (state == 103) {
    names();
  }
  else if (state == 104) {
    tanysh();
  }
  else if (state == 105) {
    nice();
  }
  else if (state == 106) {
    etmek();
  }
  else if (state == 107) {
    doing();
  }
  else if (state == 108) {
    nire();
  }
  else if (state == 109) {
    where();
  }
  else if (state == 110) {
    diller();
  }
  else if (state == 111) {
    lang();
  }
  else if (state == 112) {
    howa();
  }
  else if (state == 113) {
    weather();
  }
  else if (state == 7) {
    if (prev != state) {
      music();
    }
  }
  else if (state == 10) {
    if (prev != state) {
      music1();
    }
  }
  else if (state == 11) {
    if (prev != state) {
      music2();
    }
  }
  else if (state == 12) {
    if (prev != state) {
      music3();
    }
  }
  else if (state == 13) {
    if (prev != state) {
      music4();
    }
  }
  else if (state == 8) {
    if (prev != state) {
      music_off();
    }
  }
  else if (state == 6) {
    if (prev != state) {
      dance();
    }
  }
  else if (state == 9) {
    if (prev != state) {
      dance_off();
    }
  }
  delay(1);
  prev = state;
}

void salam() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("100.wav");
    delay(5000);
  }
}


void hello() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("101.wav");
    delay(5000);
  }
}
void adym() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("108.wav");
    delay(5000);
  }
}
void names() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("102.wav");
    delay(5000);
  }
}
void tanysh() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("109.wav");
    delay(5000);
  }
}
void nice() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("103.wav");
    delay(5000);
  }
}
void etmek() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("110.wav");
    delay(5000);
  }
}
void doing() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("104.wav");
    delay(5000);
  }
}
void nire() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("113.wav");
    delay(5000);
  }
}
void where() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("107.wav");
    delay(5000);
  }
}
void diller() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("111.wav");
    delay(5000);
  }
}
void lang() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("105.wav");
    delay(5000);
  }
}
void howa() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("112.wav");
    delay(5000);
  }
}
void weather() {
  if (prev != state) {
    saz.setVolume(5);
    saz.play("106.wav");
    delay(5000);
  }
}
void music4() {
  saz.setVolume(5);
  saz.play("4.wav");
  digitalWrite(7, HIGH);
}
void music1() {
  saz.setVolume(5);
  saz.play("5.wav");
  digitalWrite(7, HIGH);
}
void music2() {
  saz.setVolume(5);
  saz.play("6.wav");
  digitalWrite(7, HIGH);
}
void music3() {
  saz.setVolume(5);
  saz.play("7.wav");
  digitalWrite(7, HIGH);
}
void music() {
  saz.setVolume(5);
  saz.play("8.wav");
  digitalWrite(7, HIGH);
}
void music_off() {
  saz.setVolume(5);
  saz.play("2.wav");
  digitalWrite(7, LOW);
}
void dance()
{ saz.setVolume(5);
  saz.play("3.wav");
  digitalWrite(7, HIGH);

  for (int i = 0; i < 200; i++) {

    //================================================
    if (BT.available() > 0) {
      state = BT.read();
      Serial.println(state);
      if (state > 10) {

      }
    }

    if (state == 9) {
      if (prev != state) {
        dance_off();
      }
      break;
    }
    //=================================================Dance off????

    pwm.setPWM(0, 0, pulseWidth(90));
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(180));
    delay(500);
    pwm.setPWM(0, 0, pulseWidth(30));
    pwm.setPWM(1, 0, pulseWidth(150));
    pwm.setPWM(2, 0, pulseWidth(90));
    pwm.setPWM(3, 0, pulseWidth(0));
    delay(500);
    pwm.setPWM(0, 0, pulseWidth(180));
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(2, 0, pulseWidth(180));
    pwm.setPWM(3, 0, pulseWidth(90));
    delay(500);
    pwm.setPWM(0, 0, pulseWidth(100));
    pwm.setPWM(1, 0, pulseWidth(0));
    pwm.setPWM(2, 0, pulseWidth(0));
    pwm.setPWM(3, 0, pulseWidth(0));
    delay(500);
    pwm.setPWM(0, 0, pulseWidth(30));
    pwm.setPWM(1, 0, pulseWidth(150));
    pwm.setPWM(2, 0, pulseWidth(90));
    pwm.setPWM(3, 0, pulseWidth(90));
    delay(500);
  }
}
void dance_off() {
  saz.setVolume(5);
  saz.play("2.wav");
  digitalWrite(7, LOW);
  pwm.setPWM(0, 0, pulseWidth(180));
  pwm.setPWM(1, 0, pulseWidth(0));
  pwm.setPWM(2, 0, pulseWidth(90));
  pwm.setPWM(3, 0, pulseWidth(90));
}
