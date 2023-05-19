#include <AFMotor.h> 
AF_DCMotor MotorFR(1);
AF_DCMotor MotorFL(2);
AF_DCMotor MotorBL(3);
AF_DCMotor MotorBR(4);

 const int ledPin = A5; 
String readString; 

void setup()
{ 
  Serial.begin(9600); 
Serial.println("*Robot Remote Control Mode*");

pinMode (ledPin, OUTPUT);

// turn off motor 
MotorFL.run(RELEASE);
MotorFR.run(RELEASE); 
MotorBL.run(RELEASE);
MotorBR.run(RELEASE); 
}
void loop()
{ 
  while (Serial.available() > 0) {
    char command = Serial.read();
     Serial.println(command); 
     
     switch(command){
      case 'F': // move forward 
      MotorFL.run(FORWARD); 
      MotorFR.run(FORWARD); 
      MotorBL.run(FORWARD); 
      MotorBR.run(FORWARD); 
      break;
      
      case 'B': // move backward 
 
      MotorFL.run(BACKWARD);
      MotorFR.run(BACKWARD);
      MotorBL.run(BACKWARD); 
      MotorBR.run(BACKWARD);
      break; 
      case 'R': // turn right 
      
      MotorFL.run(FORWARD);
      MotorFR.run(BACKWARD);
      MotorBL.run(FORWARD); 
      MotorBR.run(BACKWARD); 
      break;
      case 'L': // turn left
      
      MotorFL.run(BACKWARD);
      MotorFR.run(FORWARD); 
      MotorBL.run(BACKWARD);
      MotorBR.run(FORWARD); 
      break; 
   case 'S':
   // stop
   MotorFL.run(RELEASE);
   MotorFR.run(RELEASE);
   MotorBL.run(RELEASE);
   MotorBR.run(RELEASE); 
   break;  
     }
  }
}

 
