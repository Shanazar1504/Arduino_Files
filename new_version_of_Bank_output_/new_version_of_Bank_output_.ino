#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <MFRC522.h>
#include <SPI.h>

const int ROW_NUM = 4;
const int COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {A0, A1, A2, A3};
byte pin_column[COLUMN_NUM] = {2, 3, 4, 5};

#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

LiquidCrystal_I2C lcd(0x27, 16, 2);

String pinCode = "";
  String denominationStr = "";
float totalValue = 0.0;
float dispensedAmount = 0.0;
int ir_val_cash;
int dis_cash = 00;
int timer;
const int ir_cash = 6;
const int ir_card = 7;
const int motor = 8;
const String correctPin = "5565";
char key;

// Denominations
float denominations[] = {1.0, 5.0, 10.0, 20.0, 50.0, 100.0}; // Default denominations

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  keypad.setDebounceTime(10);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Arduino ATM");
  lcd.setCursor(0, 1);
  lcd.print("System");
  pinMode(ir_cash, INPUT);
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);
}

void loop() {
  getRFID();
  key = keypad.getKey();


  if (key != NO_KEY) {
    const int ir_card = 7;
    Serial.println(key);
    processKeypadInput(key);
  }
}

void processKeypadInput(char key) {
  switch (key) {
    case 'B':
      Serial.println("Balance Inquiry");
      checkBalance();
      break;
    case 'A':
      Serial.println("Withdraw Money");
      getRFID();
      break;
    case 'D':
      Serial.println("Resetting");
      resetVariables();
      break;
    case '#':
      setDenominations();
      break;
  }
}

void startFunction() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card inserted");
  lcd.setCursor(0, 1);
  lcd.print("Press A");

  while (keypad.getKey() != 'A') {
    delay(100);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card inserted");
  lcd.setCursor(0, 1);
  lcd.print("Enter PIN:");

  pinCode = "";
  while (pinCode.length() < 4) {
    char key = keypad.getKey();
    if (key != NO_KEY && isDigit(key)) {
      pinCode += key;
      lcd.print('*');
    }
  }

  if (pinCode == correctPin) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PIN Accepted");
    lcd.setCursor(0, 1);
    lcd.print("Processing...");
    enterAmount();
    dispenseCash();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Incorrect PIN");
    delay(2000);
  }
}

void dispenseCash() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dispensing cash...");

  ir_val_cash = digitalRead(ir_cash);


  for (int i = sizeof(denominations) / sizeof(denominations[0]) - 1; i >= 0; i--) {
    while (dispensedAmount + denominations[i] <= totalValue) {
      Serial.println(denominationStr[i]);
      timer = int((totalValue) * 5);
      Serial.println(timer);
//      ir_val = digitalRead(ir);
//      Serial.println(ir_val);

      //      if (ir_val == HIGH) {
      //
      //        Serial.println("Infrared sensor triggered");
      //
      //      }
      //      else {
      //        dis_cash +=
      //
      //      }
      digitalWrite(motor, HIGH);
      delay(timer);
      digitalWrite(motor, LOW);
      dispensedAmount += denominations[i];
      lcd.setCursor(0, 1);
      lcd.print("Dispensed: $" + String(dispensedAmount));
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cash dispensed");
  lcd.setCursor(0, 1);
  lcd.print("Amount: $" + String(totalValue));
  delay(2000);

  dispensedAmount = 0.0;
  resetVariables();
}


void getRFID() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      dumpCardDetails();
      mfrc522.PICC_HaltA();
      return;
    }
  } else {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Arduino ATM");
    lcd.setCursor(0, 1);
    lcd.print("System");
  }
    delay(250);
}

void dumpCardDetails() {
  String cardUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    cardUid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.print("Card UID: ");
  Serial.println(cardUid);

  if (cardUid == "03da9dfd") {
    Serial.println("Card ID Verified");
    startFunction();
  }
}

void enterAmount() {
  lcd.clear();
  lcd.print("Enter amount:");
  String amountStr = "";
  char key;
  do {
    key = keypad.getKey();
    if (key != NO_KEY && (isdigit(key) || key == '.')) {
      amountStr += key;
      lcd.print(key);
    } else if (key == 'A') {
      break;
    }
  } while (true);

  totalValue += amountStr.toFloat();
}

void resetVariables() {
  pinCode = "";
  totalValue = 0.0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Variables reset");
  delay(2000);
}

void checkBalance() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Balance: $");
  lcd.print(totalValue);
  lcd.setCursor(0, 1);
  lcd.print("Press 'D' to reset");
  delay(2000);
}

void setDenominations() {
  lcd.clear();
  lcd.print("Enter:");

  char key;
  do {
    key = keypad.getKey();
    if (key != NO_KEY && (isdigit(key) || key == '.')) {
      denominationStr += key;
      lcd.print(key);
    } else if (key == 'A') {
      break;
    }
  } while (true);

  // Convert the entered denominations to an array
  int count = 0;
  String temp = "";
  for (int i = 0; i < denominationStr.length(); i++) {
    if (denominationStr[i] == ',' || denominationStr[i] == ';') {
      denominations[count++] = temp.toFloat();
      temp = "";
    } else {
      temp += denominationStr[i];
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Denominations set");
  delay(2000);
}
