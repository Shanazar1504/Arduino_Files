#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

long x=millis();

String stream;


int ThermistorPin = A0;

float baselineTemp = 10.0;
int Vo;

float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int settedTemp=10.0;
bool settedTempActive = true;
bool done = false;
String action;
String val;


IPAddress staticIP(192, 168, 1, 146); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ELECTRONICLAB";
const char* password = "Electronic123";
const char* deviceName = "Conditioner_control";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "conditioner_control_esp";

ESP8266WebServer server(80);
//
//void handleConditioner() {
//  String temperature = server.arg("temperature_esp");
//
// 
//  temperature.trim();
//
// 
// if (temperature.length() > 0){
//    action = getStringPartByNr(temperature,':',0);
//    val = getStringPartByNr(temperature,':',1);
//    settedTemp = val.toInt();
//    if(action=="heater"){
//      Serial.println("heater mode: ");
//      Serial.println(settedTemp);
//      settedTempActive=true;
//    }
//    if(action=="cooler"){
//      Serial.println("cooler mode: ");
//      Serial.println(settedTemp);
//      settedTempActive=true;
//    }
//  }
//  server.send(200, "text/html", "ok");
//}

void handlePong() {
 server.send(200, "text/html", device_key);
}

void returnTemp() {
 server.send(200, "text/html", "{temperature:"+String(Tc)+"}"); /*, setted:"+String(settedTemp)+"}");*/
} 

void setup() {
  Serial.begin(115200);
  delay(10);
  


  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);

  WiFi.mode(WIFI_STA);
  
  delay(500);
  Serial.println("");
  Serial.println("WiFi connected");
 
  Serial.print(WiFi.localIP());
  server.on("/ping/", handlePong);
 // server.on("/control/", handleConditioner);
  server.on("/checkTemp/", returnTemp);
  server.begin();
}
 
void loop() {
  server.handleClient();  
 // controlTemp();
  temp();
}





void temp(){
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0;
  // Serial.println(T);
   Serial.print("Temperature: "); 
  
  // Serial.print(Tf);
  // Serial.println(" F; ");
   Serial.print(Tc);
   Serial.println(" C");
   delay(2000);
}

//////// splitting text by delimeter : /////
String getStringPartByNr(String data, char separator, int index){
    int stringData = 0;
    String dataPart = "";
    for(int i = 0; i<data.length()-1; i++){
      if(data[i]==separator) {
        stringData++;
      }else if(stringData==index) {
        dataPart.concat(data[i]);
      }else if(stringData>index){
        return dataPart;
        break;
      }
    }
    return dataPart;
}
