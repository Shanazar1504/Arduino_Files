#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <MFRC522.h>
#include <SPI.h>

const int ROW_NUM    = 3; // three rows
const int COLUMN_NUM = 1;  // one columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'D'},
  {'B'},
  {'A'}
};

byte pin_rows[ROW_NUM]    = {4, 5, 6};
byte pin_column[COLUMN_NUM] = {3};

#define RST_PIN         1          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

float totalCoins = 0.0; // Total amount of coins inserted

enum Color { RED, GREEN, BLUE, PURPLE, ORANGE, YELLOW, UNKNOWN };

tcs3200 tcs(A0, A1, A2, A3, 2); // (S0, S1, S2, S3, output pin)

int red, green, blue, white, ir_val;

Color previousColor = UNKNOWN;

int money_1 = 1;
int money_5 = 5;
int money_10 = 10;
int money_20 = 20;
int money_50 = 50;
int money_100 = 100;

int ir = 7;
const int motor = 8;

void setup() {
  Serial.begin(9600);
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  keypad.setDebounceTime(10);
  lcd.init(); // Initialize the LCD
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Pay in here");
  lcd.setCursor(2, 1);
  lcd.print("Insert cash");
  pinMode(ir, INPUT);
  pinMode(motor, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    processKeypadInput(key);
  }
}

Color detectColor(int red, int green, int blue, int white) {
  if (blue > 20 && green < 33 && red < 33 && white > 55 && white < 70) {
    return BLUE;
  } else if (blue > 20 && green < 34 && red < 33 && white > 40) {
    return GREEN;
  } else if (red >= 28 && red > green && green < 30 && red > green && white < 65) {
    return RED;
  } else if (green < 10 && blue < 10 && white < 30) {
    return PURPLE;
  } else if (red < 52 && red > 39 && green > 35 && blue > 35 && white > 60) {
    return ORANGE;
  } else if (red > 45 && green > 40 && white > 90) {
    return YELLOW;
  } else {
    return UNKNOWN;
  }
}

void updateDisplay() {
  lcd.clear();
  lcd.print("Total Cash:");
  lcd.print(totalCoins);
}

void processKeypadInput(char key) {
  switch (key) {
    case 'B':
      Serial.println(key);
      startFunction();
      break;
    case 'A':
      Serial.println(key);
      acceptt();
      updateDisplay();  // Move the updateDisplay() call here
      break;
    case 'D':
      Serial.println(key);
      deleted();
      updateDisplay();  // Move the updateDisplay() call here
      break;
  }
}

void deleted() {
  lcd.clear();
  lcd.print("Deleted");
  totalCoins = 0;
}

void acceptt() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The task is");
  lcd.setCursor(2, 1);
  lcd.print("finished");
  lcd.setCursor(11, 1);
  lcd.print(totalCoins);
  delay(2000);
  getRFID();
  totalCoins = 0;
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Pay in here");
  lcd.setCursor(2, 1);
  lcd.print("Insert cash");
}

void startFunction() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Pay in here");
  lcd.setCursor(2, 1);
  lcd.print("Insert cash");

  ir_val = digitalRead(ir);
  Serial.println(ir_val);

  if (ir_val == HIGH) {
    Serial.println("Infrared sensor triggered");
  } else {
    red = tcs.colorRead('r');
    green = tcs.colorRead('g');
    blue = tcs.colorRead('b');
    white = tcs.colorRead('c');

    Serial.println("R= "); Serial.println(red); Serial.println("    ");
    Serial.println("G= "); Serial.println(green); Serial.println("    ");
    Serial.println("B= "); Serial.println(blue); Serial.println("    ");
    Serial.println("W(clear)= "); Serial.println(white); Serial.println("    ");

    digitalWrite(motor, HIGH);
    delay(2000);
    digitalWrite(motor, LOW);

    Color currentColor = detectColor(red, green, blue, white);

    digitalWrite(motor, HIGH);
    delay(6000);

    if (currentColor != previousColor) {
      // Color changed, perform action based on the new color
      switch (currentColor) {
        case RED:
          Serial.println("RED");
          money10();
          break;
        case GREEN:
          Serial.println("GREEN");
          money50();
          break;
        case BLUE:
          Serial.println("BLUE");
          money100();
          break;
        case PURPLE:
          Serial.println("PURPLE");
          money20();
          break;
        case ORANGE:
          Serial.println("ORANGE");
          money5();
          break;
        case YELLOW:
          Serial.println("YELLOW");
          money1();
          break;
        default:
          Serial.println("UNKNOWN COLOR");
      }
      previousColor = currentColor;
    }
  }
}

void getRFID() {
  // Check if a new card is present
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Select the RFID card
    if (mfrc522.PICC_ReadCardSerial()) {
      // Dump the card details
      dumpCardDetails();
      mfrc522.PICC_HaltA();    // Halt the card
    }
  } else {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Karty");
    lcd.setCursor(6, 1);
    lcd.print("degirin");
  }
}

void dumpCardDetails() {
  // Get the card UID
  String cardUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    cardUid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.print("Card UID: ");
  Serial.println(cardUid);

  if (cardUid == "63855195") {
    Serial.println("ok");
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(" Transaction");
    delay(1500);
    lcd.clear();
  }
}

void money1() {
  totalCoins += money_1;
  delay(200);
  Serial.println(totalCoins);
  updateDisplay();
}
void money5() {
  totalCoins += money_5;
  delay(200);
  Serial.println(totalCoins);
  updateDisplay();
}
void money10() {
  totalCoins += money_10;
  delay(200);
  Serial.println(totalCoins);
  updateDisplay();
}
void money20() {
  totalCoins += money_20;
  delay(200);
  Serial.println(totalCoins);
  updateDisplay();
}
void money50() {
  totalCoins += money_50;
  delay(200);
  Serial.println(totalCoins);
  updateDisplay();
}
void money100() {
  totalCoins += money_100;
  delay(200);
  Serial.println(totalCoins);
  updateDisplay();
}
