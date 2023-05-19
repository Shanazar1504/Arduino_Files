#include <SoftwareSerial.h>
SoftwareSerial bt(2, 3); // RX, TX

#include "dht.h"
#define dataPin A0
dht DHT;

int temp;
int hum;

 
 Serial.begin(9600); 
 bt.begin(9600); 
 Serial.println("Ready");
  
}

void loop(){
  int readData = DHT.read11(dataPin);

  hum = DHT.humidity;
  temp = DHT.temperature;
  
  bt.print(temp); //send distance to MIT App
 bt.print(";");
 bt.print(hum); //send distance to MIT App 
 bt.println(";");
  
  delay(1000);
}
