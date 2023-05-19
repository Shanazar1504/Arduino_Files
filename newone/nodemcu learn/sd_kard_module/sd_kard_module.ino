#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
    Serial.begin(9600);

  Serial.print("Initializing SD card...");
  bool _SD_OK=0;
  _SD_OK=SD.begin(4);

  if (_SD_OK) {
    Serial.println("SD card init done!");
  }else{
    Serial.println("Check SD card connection");
     }
  
  myFile = SD.open("read.txt");

  
  if (myFile) {
    Serial.print("Found file");
  }else{
    Serial.println("File not found");
  }
  //for(byte m=0; m<10; m++)
  while(myFile.available()){
  Serial.write(myFile.read());
  }
  myFile.close();
}

void loop(){
  
}
