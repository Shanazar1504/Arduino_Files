#include <IRremote.h>
#include "LowPower.h"

IRsend sender;

int power=4;
int mode=5;
int up=6;
int down=7;
int left=8;
int right=9;
int ok=10;
int r=11;/////////////////////
int g=12;// RGB LED (MODE LED)
int b=13;/////////////////////

int tv_repeat=3; // the data to be send 3 times for receivers like sony
int tv_data_length=25; // length of mark and space - its the first number when we receives the data from any remote. 

int ac_repeat=1; // one time is sufficient for my ac
int ac_data_length=33;

int rgb=1;
unsigned int timer=0;


/////////////////////////////////////////////// TV remote DATA////////////////////////////
unsigned int tv_onoff[]={};
unsigned int tv_volup[]={};
unsigned int tv_voldown[]={};
unsigned int tv_prev[]={};
unsigned int tv_next[]={};
unsigned int tv_source[]={};
//////////////////////////////////////////////AC remote data//////////////////////////////
unsigned int ac_onoff[]={};
unsigned int ac_tempup[]={};
unsigned int ac_tempdown[]={};
unsigned int ac_swing[]={};
unsigned int ac_fan[]={};
unsigned int ac_turbo[]={};
////////////////////////////////////////////reserved for new data////////////////////////////
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////

void (*reset)(void) = 0;
void wakeUp()
{
 timer = 0;
 if(rgb==1)//////////////////////////red light for tv 
    {
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
      digitalWrite(b,HIGH);
    }
    else if(rgb==2)/////////////////green light for ac
    {
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
      digitalWrite(b,HIGH);
    }
    else if(rgb==3)////////////////blue light reserved 
    {
      digitalWrite(r,HIGH);
      digitalWrite(g,HIGH);
      digitalWrite(b,LOW);
    }
}

void setup()
{
  Serial.begin(9600);
  pinMode(power,INPUT_PULLUP);
  pinMode(mode,INPUT_PULLUP);
  pinMode(up,INPUT_PULLUP);
  pinMode(down,INPUT_PULLUP);
  pinMode(left,INPUT_PULLUP);
  pinMode(right,INPUT_PULLUP);
  pinMode(ok,INPUT_PULLUP);
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(b,OUTPUT);

  digitalWrite(r,LOW);//OFF
  digitalWrite(g,HIGH);//OFF
  digitalWrite(b,HIGH);//OFF
  timer = 0;
  
}


void loop()
{
 attachInterrupt(0,wakeUp, HIGH);
 while (timer < 10000)
 { 
  if(digitalRead(mode)==0)
  {
    while(digitalRead(mode)==0);
    timer = 0;  
    if(rgb==3)
    {
      rgb=1;
    }
    else
    rgb+=1;

    if(rgb==1)
    {
      digitalWrite(r,LOW);
      digitalWrite(g,HIGH);
      digitalWrite(b,HIGH);
    }
    else if(rgb==2)
    {
      digitalWrite(r,HIGH);
      digitalWrite(g,LOW);
      digitalWrite(b,HIGH);
    }
    else if(rgb==3)
    {
      digitalWrite(r,HIGH);
      digitalWrite(g,HIGH);
      digitalWrite(b,LOW);
    }
  }
  else if(digitalRead(power)==0)/////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
    while(digitalRead(power)==0);
    timer = 0;  
    if(rgb==1)//tv mode
    {
     for(int i = 0; i < tv_repeat; i++) 
     {
      sender.sendRaw(tv_onoff, tv_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==2)//ac mode
    {
      for(int i = 0; i < ac_repeat; i++) 
     {
      sender.sendRaw(ac_onoff, ac_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==3)//reserved mode
    {
      ///////////////////////////////////
      ///////////////////////////////////
      ///////////////////////////////////
    }
  }
   else if(digitalRead(up)==0)/////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
    if(rgb==1)//tv mode
    {
      while(digitalRead(up)==0)
      {
        timer = 0;  
        for(int i = 0; i < tv_repeat; i++) 
        {
         sender.sendRaw(tv_volup, tv_data_length , 40);//data + length of data + carrier frequency in KHz
         delay(50);
        }
      }
    }
    
    else if(rgb==2)//ac mode
    {
      while(digitalRead(up)==0);
      timer = 0;  
      for(int i = 0; i < ac_repeat; i++) 
     {
      sender.sendRaw(ac_tempup, ac_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==3)//reserved mode
    {
      ///////////////////////////////////
      ///////////////////////////////////
      ///////////////////////////////////
    }
  }
  else if(digitalRead(down)==0)/////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
    if(rgb==1)//tv mode
    {
      while(digitalRead(down)==0)
      {
       timer = 0;  
       for(int i = 0; i < tv_repeat; i++) 
       {
        sender.sendRaw(tv_voldown, tv_data_length , 40);//data + length of data + carrier frequency in KHz
        delay(50);
       }
      }
    }
    else if(rgb==2)//ac mode
    {
      while(digitalRead(down)==0);
      timer = 0;  
      for(int i = 0; i < ac_repeat; i++) 
     {
      sender.sendRaw(ac_tempdown, ac_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==3)//reserved mode
    {
      ///////////////////////////////////
      ///////////////////////////////////
      ///////////////////////////////////
    }
  }
  else if(digitalRead(left)==0)/////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
    while(digitalRead(left)==0);
    timer = 0;  
    if(rgb==1)//tv mode
    {
     for(int i = 0; i < tv_repeat; i++) 
     {
      sender.sendRaw(tv_prev, tv_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==2)//ac mode
    {
      for(int i = 0; i < ac_repeat; i++) 
     {
      sender.sendRaw(ac_swing, ac_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==3)//reserved mode
    {
      ///////////////////////////////////
      ///////////////////////////////////
      ///////////////////////////////////
    }
  }
  else if(digitalRead(right)==0)/////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
    while(digitalRead(right)==0);
    timer = 0;  
    if(rgb==1)//tv mode
    {
     for(int i = 0; i < tv_repeat; i++) 
     {
      sender.sendRaw(tv_next, tv_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==2)//ac mode
    {
      for(int i = 0; i < ac_repeat; i++) 
     {
      sender.sendRaw(ac_fan, ac_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==3)//reserved mode
    {
      ///////////////////////////////////
      ///////////////////////////////////
      ///////////////////////////////////
    }
  }
  else if(digitalRead(ok)==0)/////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
    while(digitalRead(ok)==0);
    timer = 0;  
    if(rgb==1)//tv mode
    {
     for(int i = 0; i < tv_repeat; i++) 
     {
      sender.sendRaw(tv_source, tv_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==2)//ac mode
    {
      for(int i = 0; i < ac_repeat; i++) 
     {
      sender.sendRaw(ac_turbo, ac_data_length , 40);//data + length of data + carrier frequency in KHz
      delay(50);
     }
    }
    else if(rgb==3)//reserved mode
    {
      ///////////////////////////////////
      ///////////////////////////////////
      ///////////////////////////////////
    }
  }
  delay(1);
  timer = timer + 1;
 }
 digitalWrite(r,HIGH);
 digitalWrite(g,HIGH);
 digitalWrite(b,HIGH);
 LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}
