#include <Arduino.h>
#include "Wire.h"
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"
#include "audiodata.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
WiFiClient client;
ESP8266WebServer server(80); /* defining server port */

const char* ssid = "OGUZHAN"; /* Your SSID */
const char* password = "1020304050"; /* Your Password */

String  data = "";
Servo ms;
int pos;
void setup()
{
  ms.attach(0);
  Serial.begin(115200);
  Serial.println("GPIO test!");

   /* Connecting to WiFi */
  connectToWiFi();

  server.on("/", handleRequest);
  server.onNotFound(handleRequest);

  /* Starting Server */
  server.begin();
  Serial.println("Server started");

}

void loop() {
  server.handleClient();
  data = server.arg("data");

  if (data != "") {

    if (data.equalsIgnoreCase("hi")) {
      say_hi();
    }
    if (data.equalsIgnoreCase("what is your name") || data.equalsIgnoreCase("your name")) {
      my_name_hash();
    }
    if (data.equalsIgnoreCase("nice to meet you") || data.equalsIgnoreCase("glad to meet you")) {
      nice_to_meet_you_too();
    }
    if (data.equalsIgnoreCase("introduce yourself") || data.equalsIgnoreCase("what are you")) {
      i_am_humanoid_robot();
    }
    if (data.equalsIgnoreCase("you are amazing") || data.equalsIgnoreCase("you look amazing")) {
      thank_you();
    }
    if (data.equalsIgnoreCase("are you happy being a robot") || data.equalsIgnoreCase("do you hate mathematics")) {
      say_yes();
    }
    if (data.equalsIgnoreCase("do you love me") || data.equalsIgnoreCase("tell me your secrets")) {
      say_no();
    }
    if (data.equalsIgnoreCase("tell viewers to subscribe") || data.equalsIgnoreCase("tell them to subscribe")) {
      say_subscribe();
    }
    if (data.equalsIgnoreCase("bye")) {
      say_bye();
    }
  }
  data = "";
}

/* Reuest and resonse handling */
void handleRequest() {
  if ( server.hasArg("data") ) {
    Serial.println(server.arg("Key"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void connectToWiFi() {
  delay(3000);
  WiFi.disconnect();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(500);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  Serial.println("\n");
  delay(5000);
}

void initial_position() {
  int pos;
  ms.write(90);
}
 
void say_hi() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( hi, sizeof(hi) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int pos = 0; pos <= 180; pos++) {
  ms(0, 0 + pos);
  delay(1000);
  }
  for (int pos = 180; i <= 0; pos++) {
      ms(0, 180 - pos);
      if (!wav->loop()) wav->stop();
      delay(1000);
  }
}

/******************** my name is hash ********************/
void my_name_hash() {

  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( mynamehash, sizeof(mynamehash) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
}
 
void nice_to_meet_you_too() {

  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( nicetomeetyoutoo, sizeof(nicetomeetyoutoo) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);


}

/******************** i am humanoid robot ********************/
void i_am_humanoid_robot() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( iamhumanoid, sizeof(iamhumanoid) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

 }

/******************** thank you ********************/
void thank_you() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( thankyou, sizeof(thankyou) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

 }

/******************** yes ********************/
void say_yes() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( sayyes, sizeof(sayyes) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

 }

/******************** no ********************/
void say_no() {

  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( sayno, sizeof(sayno) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

 }

//******************** subscribe ********************//
void say_subscribe() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( subscribe, sizeof(subscribe) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  }

//******************** bye ********************//
void say_bye() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( bye, sizeof(bye) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

 }
