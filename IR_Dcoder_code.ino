#include <IRremote.h>

IRrecv receiver(2); 
decode_results results;

void setup() 
{
  Serial.begin(9600);
  receiver.enableIRIn(); // start receiving signals
}

void loop() 
{
  if(receiver.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    Serial.print(results.rawlen - 1);
    for(int i = 1; i < results.rawlen; i++) 
    {
      unsigned int num = results.rawbuf[i] * USECPERTICK;
      Serial.print(",");
      Serial.print(num);
    }
    Serial.println("");
    receiver.resume();
  }
  
}
