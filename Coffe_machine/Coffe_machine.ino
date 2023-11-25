#include <LiquidCrystal_I2C.h>
const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int buttonPin3 = 6;
bool buttonState1 = false;
bool buttonState2 = false;
bool buttonState3 = false;
const int motor1 = 11;
const int motor2 = 12;
const int motor3 = 13;
const int ir1 = 8;
const int ir2 = 9;
const int ir3 = 10;
float counter;


LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {

  int irValue1 = digitalRead(ir1);
  int irValue2 = digitalRead(ir2);
  int irValue3 = digitalRead(ir3);

  int Button1 = digitalRead(buttonPin1);
  int Button2 = digitalRead(buttonPin2);
  int Button3 = digitalRead(buttonPin3);
  Serial.println(Button1);
  Serial.println(Button2);
  Serial.println(Button3);
    Serial.println(irValue1);
  Serial.println(irValue2);
  Serial.println(irValue3);
  delay(50);


  if (irValue1 == LOW) {
    counter = counter + 0.50;
  }

  if (irValue2 == LOW) {
    counter = counter + 1;
  }

  if (irValue3 == LOW) {
    counter = counter + 2;
  }

  Serial.print("Money: ");
  Serial.println(counter);


  if (Button1 == HIGH) {
    buttonState1 = !buttonState1;
    buttonState2 = false;
    buttonState3 = false;
    delay(1000);
  }

  if (Button2 == HIGH) {
    buttonState2 = !buttonState2;
    buttonState1 = false;
    buttonState3 = false;
    delay(1000);
  }

  if (Button3 == HIGH) {
    buttonState3 = !buttonState3;
    buttonState2 = false;
    buttonState1 = false;
    delay(1000);
  }
  if (buttonState1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("KOFFE");
    lcd.setCursor(6, 0);
    lcd.print("Baha:");
    lcd.setCursor(12, 0);
    lcd.print("3TMT");
    lcd.setCursor(0, 1);
    lcd.print("Toleg:");
    lcd.setCursor(9, 1);
    lcd.print(counter);
    if (counter == 3.00) {
      digitalWrite(motor1, HIGH);
      delay(5000);
      digitalWrite(motor1, LOW);
      buttonState1 = false;
      counter = 0;
    }
  }
  if (buttonState2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CAY");
    lcd.setCursor(6, 0);
    lcd.print("Baha:");
    lcd.setCursor(12, 0);
    lcd.print("2TMT");
    lcd.setCursor(0, 1);
    lcd.print("Toleg:");
    lcd.setCursor(9, 1);
    lcd.print(counter);
    if (counter == 2.00) {
      digitalWrite(motor2, HIGH);
      delay(5000);
      digitalWrite(motor2, LOW);
      buttonState2 = false;
      counter = 0;
    }
  }
  if (buttonState3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SUW");
    lcd.setCursor(4, 0);
    lcd.print("Baha:");
    lcd.setCursor(10, 0);
    lcd.print("1.50TMT");
    lcd.setCursor(0, 1);
    lcd.print("Toleg:");
    lcd.setCursor(9, 1);
    lcd.print(counter);
    if (counter == 1.50) {
      digitalWrite(motor3, HIGH);
      delay(5000);
      digitalWrite(motor3, LOW);
      buttonState3 = false;
      counter = 0;
    }
  }
  if (buttonState1 == false && buttonState2 == false && buttonState3 == false) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NAME ISLEYAN");
  }
}
