#include <ESP8266WiFi.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiUdp.h>

//#include <SPI.h>
//#include <WiFi.h>
//#include <WiFiUdp.h>
//#include <ESP8266.h>
//#include <Servo.h>

const char* ssid = "YVRB";
const char* password = "YGreater";

char buff[] = "";

String states;

WiFiUDP Udp;
unsigned int port = 25666;
char packet[255];

bool q,w,e,r,t,y,u,ii,o,a,s,d,f,g,j;

IPAddress ip(192, 168, 31, 249);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {

pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  
  Serial.begin(115200);
  Serial.println();

 // SPI.begin();

  //gate.attach(8);

  //WiFi.hostname("YVRB");
  WiFi.config(ip, gateway, subnet);

  //delay(120000);

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connection Successful");
  Udp.begin(port);
  Serial.printf("Listener started at IP %s, at port %d", WiFi.localIP().toString().c_str(), port);
  Serial.println();

  
}

void loop() {
  
  delay(50);
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received %d bytes from %s, port %d", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(packet, 255);
    if (len > 0) {
      packet[len] = 0;
    }
    Serial.printf("UDP packet contents: %s", packet);
    Serial.println();

    String dataraw = packet, data;

    for (int j = 0; j < dataraw.length(); j++) {
      if (dataraw[j] != '!')
        data += dataraw[j];
      else {

        //Serial.println(data);

        for (int i = 0; i < data.length() - 1; i++) {
          if (data[i] == '*') {
            if (data[i + 1] == 'j') {
              Serial.println("j");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                i=false;
                o=false;
                a=false;
                s=false;
                d=false;
                f=false;
                j=true;
            }else
            if (data[i + 1] == 'q') {
              Serial.println("q");
                q=true;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                i=false;
                g=false;
                o=false;
                a=false;
                s=false;
                d=false;
                f=false;
                j=false;
            }else
            if (data[i + 1] == 'w') {
              Serial.println("w");
                q=false;
                w=true;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                g=false;
                i=false;
                o=false;
                a=false;
                s=false;
                d=false;
                f=false;
                j=false;
            }else
            if (data[i + 1] == 'e') {
              Serial.println("e");
                q=false;
                w=false;
                e=true;
                r=false;
                t=false;
                y=false;
                u=false;
                i=false;
                o=false;
                a=false;
                s=false;
                g=false;
                d=false;
                f=false;
                j=false;
            }else
            if (data[i + 1] == 'r') {
              Serial.println("r");
                q=false;
                w=false;
                e=false;
                r=true;
                t=false;
                y=false;
                u=false;
                i=false;
                o=false;
                a=false;
                g=false;
                s=false;
                d=false;
                f=false;
                j=false;
            }else
            if (data[i + 1] == 't') {
              Serial.println("t");
                q=false;
                w=false;
                e=false;
                r=false;
                t=true;
                y=false;
                u=false;
                i=false;
                o=false;
                a=false;
                g=false;
                s=false;
                d=false;
                f=false;
                j=false;
            }else
            if (data[i + 1] == 'y') {
              Serial.println("y");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=true;
                u=false;
                i=false;
                o=false;
                a=false;
                s=false;
                d=false;
                f=false;
                j=false;
                g=false;
            }else
            if (data[i + 1] == 'u') {
              Serial.println("u");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=true;
                i=false;
                o=false;
                a=false;
                s=false;
                d=false;
                f=false;
                g=false;
                j=false;
            }else
            if (data[i + 1] == 'i') {
              Serial.println("i");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                ii=true;
                o=false;
                a=false;
                s=false;
                d=false;
                f=false;
                g=false;
                j=false;
            }else
            if (data[i + 1] == 'o') {
              Serial.println("o");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                ii=false;
                o=true;
                a=false;
                s=false;
                d=false;
                f=false;
                g=false;
                j=false;
            }else
            if (data[i + 1] == 'a') {
              Serial.println("a");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                ii=false;
                o=false;
                a=true;
                s=false;
                d=false;
                f=false;
                g=false;
                j=false;
            }else
            if (data[i + 1] == 's') {
              Serial.println("s");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                ii=false;
                o=false;
                a=false;
                s=true;
                d=false;
                f=false;
                g=false;
                j=false;
            }else
            if (data[i + 1] == 'd') {
              Serial.println("d");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                ii=false;
                o=false;
                a=false;
                s=false;
                d=true;
                f=false;
                g=false;
                j=false;
            }else
            if (data[i + 1] == 'f') {
              Serial.println("f");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                ii=false;
                o=false;
                a=false;
                s=false;
                d=false;
                f=true;
                g=false;
                j=false;
            }else
            if (data[i + 1] == 'g') {
              Serial.println("g");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                ii=false;
                o=false;
                a=false;
                s=false;
                d=false;
                f=false;
                g=true;
                j=false;
            }else
            if (data[i + 1] == 'z') {
              Serial.println("z");
                q=false;
                w=false;
                e=false;
                r=false;
                t=false;
                y=false;
                u=false;
                ii=false;
                o=false;
                a=false;
                s=false;
                d=false;
                f=false;
                }
            
            //delay(300);
          }
        }
        data = "";
      }
    }

    /*
    if (a){
      digitalWrite(D8,1);
    }else{
      digitalWrite(D8,0);
    }
    if (s){
      digitalWrite(D0,1);
    }else{
      digitalWrite(D0,0);
    }
    if (d){
      digitalWrite(D0,1);
    }else{
      digitalWrite(D0,0);
    }
    if (f){
      digitalWrite(D0,1);
    }else{
      digitalWrite(D0,0);
    }
*/

    /*const char * camdata=esp.readData().c_str();

      Serial.println("camdata:");
      Serial.println(camdata);*/


    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write((("Data").c_str(),2););
    Udp.endPacket();
  }

  if (j){
      digitalWrite(D0,1);
            
    }else{
      digitalWrite(D0,0);
               
    }
    if (q){
      digitalWrite(D1,1);
         
    }else{
      digitalWrite(D1,0);
        
    }
    if (w){
      digitalWrite(D1,1);
              
    }else{
      digitalWrite(D1,0);
         
    }
    if (e){
      digitalWrite(D2,1);
               
    }else{
      digitalWrite(D2,0);
               
    }
    if (r){
      digitalWrite(D3,1);
               
    }else{
      digitalWrite(D3,0);
              
    }
    if (t){
      digitalWrite(D4,1);
               
    }else{
      digitalWrite(D4,0);
         
    }
    if (y){
      digitalWrite(D5,1);
               
    }else{
      digitalWrite(D5,0);
               
    }
    if (u){
      digitalWrite(D6,1);
         
    }else{
      digitalWrite(D6,0);
             
    }
    if (ii){
      digitalWrite(D7,1);
               
    }else{
      digitalWrite(D7,0);
               
    }
    if (o){
      digitalWrite(D8,1);
               
    }else{
      digitalWrite(D8,0);
               
    }
}