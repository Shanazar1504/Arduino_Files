//AUTHOR by amirdadfar9192

  #include <ESP8266WiFi.h>
  #include <WiFiClient.h> 
  #include <ESP8266WebServer.h>

  const int ledPin = D4;
  const int ldrPin = A0;
  int brightness1 = 60;
  int brightness2 = 120;
  int brightness3 = 180;
  int brightness4 = 255;
  int cycle, dutyCycle, ldrStatus;

  String command;
  
  const char* ssid = "LDR_01"; // put WIFI SSID for creating AP     
  const char* pass = "12345678"; // put WIFI password for creating AP
  ESP8266WebServer server(80);
  
  void setup() {
  
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.on("/led0", led0);
     server.on("/led1", led1);
     server.on("/led2", led2);
     server.on("/led3", led3);
     server.on("/led4", led4);     
     server.on("/set", ldrSet);
     server.on("/catch", ldrCatch);

     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}


void led0(){ 
  server.send(200, "text/html", "0");
  digitalWrite(ledPin, 0);
  Serial.println("led 0");
  }

void led1(){ 
  server.send(200, "text/html", "1");
  analogWrite(ledPin, brightness1);
  Serial.println("led 1");
  }

void led2(){ 
  server.send(200, "text/html", "2");
  analogWrite(ledPin, brightness2);
  Serial.println("led 2");
  }

void led3(){ 
  server.send(200, "text/html", "3");
  analogWrite(ledPin, brightness3);
  Serial.println("led 3");
  }

void led4(){ 
  server.send(200, "text/html", "4");
  analogWrite(ledPin, brightness4);
  Serial.println("led 4");
  }

  void ldrCatch(){ 
  ldrStatus = analogRead(ldrPin);
  cycle = ldrStatus * (255 / 1023.0);
  String myCycle = String(cycle);
  server.send(200, "text/html", myCycle);
  Serial.println("led catch -> " + cycle);
  }

  
void ldrSet() {
        
//  ldrStatus = analogRead(ldrPin);
//
//  cycle = ldrStatus * (255 / 1023.0);
  
  if (cycle >= 220) {
     for(dutyCycle = cycle; dutyCycle < brightness1; dutyCycle++){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(cycle + "bright 1");
   } 

    else if (cycle >= 230) {
     for(dutyCycle = cycle; dutyCycle < brightness2; dutyCycle++){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(cycle + "bright 2");
   }
  
    else if (cycle >= 240) {
     for(dutyCycle = cycle; dutyCycle < brightness3; dutyCycle++){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(cycle + "bright 3");
   } 
  
   else if (cycle >= 255) {
     for(dutyCycle = cycle; dutyCycle < brightness4; dutyCycle++){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(cycle + "bright 4");
   }
  
    else if (cycle <= 200) {
     for(dutyCycle = cycle; dutyCycle > 0; dutyCycle--){ 
       analogWrite(ledPin, dutyCycle);
       delay(1);
     }
     Serial.println(cycle + "bright 0");
   }
   
}


void loop() {
   
    server.handleClient();

    command = server.arg("State");
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
