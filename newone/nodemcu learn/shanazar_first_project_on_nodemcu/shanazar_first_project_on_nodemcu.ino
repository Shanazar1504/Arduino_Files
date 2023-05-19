#include<Servo.h> 
Servo myservo;
//int pos;
void setup() {
  Serial.begin(9600);
myservo.attach(4);
 myservo.write(0);
 delay(0);

}

void loop()
{
for(int i = 0 ; i <= 180 ; i ++){
  myservo.write(i);
 delay(100);
}
   
}
