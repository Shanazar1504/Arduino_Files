#include "SPI.h"
#include "MFRC522.h"
#include<Servo.h>
int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
double total = 0;
int count_prod = 0;
int a;
#define Buzzer 4   
#define SS_PIN 10
#define RST_PIN 9
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
Servo s;

  int sw = 0;
void setup() {
    pinMode(A3, INPUT_PULLUP);

  lcd.init();
  lcd.clear();         
  lcd.backlight();  
  s.attach(8);
  s.write(0);
  Serial.begin (9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode (7, INPUT);
  lcd.setCursor(0, 0);
  lcd.print(" Akylly Araba");
  delay (2000);
  lcd.setCursor(0, 1);
  lcd.print(" Sowda Karty");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HOS GELDINIZ!");
  delay (2000);
  lcd.setCursor(2, 1);
  lcd.print("OGUZHAN MARKET");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sowda Kartyny");
  lcd.setCursor(3, 1);
  lcd.print("Goyun");
//  pinMode(4, OUTPUT);
  pinMode(Buzzer, OUTPUT);

}

char c[32];
  int i = 0;

  char pass[20] = {'2','7','5','9','5','9'};

  
void loop() {
      int a = digitalRead(A3);

//  sw=digitalRead(A0);
 // if (sw==HIGH){s.write (85); delay(10000); s.write(0);}

if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO");
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

 
  Serial.print("Tap card key: ");

  Serial.println(strID);
  if ((strID.indexOf("03:79:B0:18") >=0)&&(a==1)) {
    oc();}
    if ((strID.indexOf("03:79:B0:18") >=0)&&(a==0)) {
    oc1();
  }else if ((strID.indexOf("0A:30:14:3F") >=0)&&(a==1)) {
    bc();
  }else if ((strID.indexOf("0A:30:14:3F") >=0)&&(a==0))  {
    bc1();
  }
  else if ((strID.indexOf("55:38:48:59") >=0)&&(a==1))  {
    dc();
  }else if ((strID.indexOf("55:38:48:59") >=0)&&(a==0))  {
    dc1();
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}


void oc(){
   digitalWrite(Buzzer, HIGH); 
   delay(200);
   digitalWrite(Buzzer, LOW); 
   delay(500);
   lcd.setCursor(0, 0);
    lcd.print("SUYT goshuldy      ");
    lcd.setCursor(0, 1);
    lcd.print("Price :+ 20.00      ");
    p2++;
     
    delay(2000);
    total = total + 20.00;
    count_prod++;
         lcd.clear();

    lcd.setCursor(3, 0);
    lcd.print("Jemi:");
    lcd.setCursor(3, 1);
    lcd.print(total);
   
    
    
  
}

void oc1(){
  if(total>0){ 
    digitalWrite(Buzzer, HIGH); 
   delay(200);
   digitalWrite(Buzzer, LOW); 
   delay(500);
   lcd.setCursor(0, 0);
    lcd.print("SYYT  Ayyryldy    ");
    lcd.setCursor(0, 1);
    lcd.print("Bahasy :- 20.00      ");
    p2--;
    delay(2000);
    total = total - 20.00;
    count_prod--;
         lcd.clear();

    lcd.setCursor(3, 0);
    lcd.print("Jemi:");
    lcd.setCursor(3, 1);
    lcd.print(total);
  }else{
    lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not in cart!!! ");
  }
    
  
}

void dc(){
   digitalWrite(Buzzer, HIGH); 
   delay(200);
   digitalWrite(Buzzer, LOW); 
   delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Mesge goshuldy      ");
    lcd.setCursor(0, 1);
    lcd.print("Price :+ 10.00      ");
    p1++;
     delay(2000);
    total = total + 10.00;
    count_prod++;
    lcd.clear();
    
    lcd.setCursor(3, 0);
    lcd.print("Jemi:");
    lcd.setCursor(3, 1);
    lcd.print(total);
}
void dc1(){
   digitalWrite(Buzzer, HIGH); 
   delay(200);
   digitalWrite(Buzzer, LOW); 
   delay(500);
  if(total>0){
    lcd.setCursor(0, 0);
    lcd.print(" MESGE AYYRYLDY      ");
    lcd.setCursor(0, 1);
    lcd.print("Bahasy :-10.00      ");
    p1--;
     delay(2000);
    total = total - 10.00;
    count_prod--;
    lcd.clear();
    
    lcd.setCursor(3, 0);
    lcd.print("Jemi:");
    lcd.setCursor(3, 1);
    lcd.print(total);}
    else{  lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not in cart!!!        ");}
}
void bc(){
   digitalWrite(Buzzer, HIGH); 
   delay(200);
   digitalWrite(Buzzer, LOW); 
   delay(500);
   lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CAY goshuldy       ");
    lcd.setCursor(0, 1);
    lcd.print("Price :25.00      ");
    p3++;
     delay(2000);
    total = total + 25;
    count_prod++;
    lcd.clear();
    
    lcd.setCursor(3, 0);
    lcd.print("Jemi:");
    lcd.setCursor(3, 1);
    lcd.print(total);
}void bc1(){
   digitalWrite(Buzzer, HIGH); 
   delay(200);
   digitalWrite(Buzzer, LOW); 
   delay(500);
  if(total>0){
  
   lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CAY ayyryldy      ");
    lcd.setCursor(0, 1);
    lcd.print("Bahasy :25.00      ");
    p3--;
     delay(2000);
    total = total - 25;
    count_prod--;
    lcd.clear();
    
    lcd.setCursor(3, 0);
    lcd.print("Jemi:");
    lcd.setCursor(3, 1);
    lcd.print(total);}
else{
  lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Not in cart!!!        ");}}
