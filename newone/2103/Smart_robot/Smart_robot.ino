/* Including libraries  */
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
ESP8266WebServer server(80);

const char* ssid = "Smart_robot"; /* Your SSID */
const char* password = "21032002"; /* Your Password */

String  data = "";
Servo x;
Servo y;

void setup()
{
  Serial.begin(115200);
  Serial.println("GPIO test!");
  x.attach(0);/* Pin D0 */
  y.attach(2);/* Pin D2 */

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

    if (data.equalsIgnoreCase("salon") || data.equalsIgnoreCase("alarm") || data.equalsIgnoreCase("set alarm")) {
      say_hi();
    }
    if (data.equalsIgnoreCase("Adam Nana") || data.equalsIgnoreCase("Autumn near me")) {
      my_name_hash();
    }
    if (data.equalsIgnoreCase("Thomas anema shot") || data.equalsIgnoreCase("time to send a massage") || data.equalsIgnoreCase("Sunshine massage")) {
      nice_to_meet_you_too();
    }
    if (data.equalsIgnoreCase("send near Ayden") || data.equalsIgnoreCase("10 Meriden") || data.equalsIgnoreCase("in Meriden") || data.equalsIgnoreCase("chimney reading")) {
      i_am_humanoid_robot();
    }
    if (data.equalsIgnoreCase("hi Toyota") || data.equalsIgnoreCase("high heel") || data.equalsIgnoreCase("how you feel") || data.equalsIgnoreCase("hytale") || data.equalsIgnoreCase("highfield")) {
      thank_you();
    }
    if (data.equalsIgnoreCase("all done") || data.equalsIgnoreCase("all the time") || data.equalsIgnoreCase("always hun") || data.equalsIgnoreCase("alton") || data.equalsIgnoreCase("open")) {
      say_yes();
    }
    if (data.equalsIgnoreCase("faculty at") || data.equalsIgnoreCase("soccernet")) {
      say_no();
    }
    if (data.equalsIgnoreCase("hi fiddler") || data.equalsIgnoreCase("how to delete")) {
      say_subscribe();
    }
    if (data.equalsIgnoreCase("hush")) {
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
void say_hi() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( hi, sizeof(hi) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  x.write(180);
  y.write(180);
  delay(2000);

  x.write(0);
  y.write(0);

  if (!wav->loop()) wav->stop();
  delay(10);
}
void my_name_hash() {

  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( mynamehash, sizeof(mynamehash) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  if (!wav->loop()) wav->stop();
  delay(10);
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

  if (!wav->loop()) wav->stop();
  delay(15);
}
void i_am_humanoid_robot() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( iamhumanoid, sizeof(iamhumanoid) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  if (!wav->loop()) wav->stop();
  delay(15);
}
void thank_you() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( thankyou, sizeof(thankyou) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  if (!wav->loop()) wav->stop();
  delay(15);
}
void say_yes() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( sayyes, sizeof(sayyes) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  if (!wav->loop()) wav->stop();
  delay(15);
}
void say_no() {

  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( sayno, sizeof(sayno) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  if (!wav->loop()) wav->stop();
  delay(10);
}
void say_subscribe() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( subscribe, sizeof(subscribe) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  if (!wav->loop()) wav->stop();
  delay(15);
}
void say_bye() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( bye, sizeof(bye) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  if (!wav->loop()) wav->stop();
  delay(10);
}
