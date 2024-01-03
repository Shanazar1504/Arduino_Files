#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address and dimensions (change if necessary)

Servo myservo;
int pos = 0;
const int button1 = 2;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  //  digitalWrite(button1, 0);
  // Set up LCD
  lcd.init();
  lcd.backlight();
  myservo.attach(9);
  lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Organized ");
}

void loop() {
  if (digitalRead (button1) == 1) {
    //  Serial.println("pressed");
    //  myservo.write(90);
    //  delay(1000);
    //  myservo.write(0);
  }
  else {
    Serial.println("unpressed");
    //     lcd.clear();
    //  lcd.setCursor(2, 0);
    //  lcd.print("No organized ");
  }
}
void pill_dis() {
  // Display initial values on LCD
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Time: ");
  //  lcd.print(setHour, setMinute);
}
