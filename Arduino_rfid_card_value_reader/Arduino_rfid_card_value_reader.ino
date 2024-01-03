#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9   // Configurable, see typical pin layout above
#define SS_PIN 10   // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

float totalCoins = 123.45;  // Replace with your actual totalCoins value

const int BLOCK_SIZE = 16; // Size of data block

void setup() {
  Serial.begin(9600);
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  lcd.init();          // Initialize the LCD
  lcd.backlight();
}

void loop() {
  // Check if a new card is present
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Select the RFID card
    if (mfrc522.PICC_ReadCardSerial()) {
      // Write totalCoins to the RFID card
      writeTotalCoinsToCard(totalCoins);

      // Dump the card details
      dumpCardDetails();

      mfrc522.PICC_HaltA();    // Halt the card
    }
  }
}

void writeTotalCoinsToCard(float totalCoins) {
  // Get the card UID
  String cardUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    cardUid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.print("Card UID: ");
  Serial.println(cardUid);

  // Check if the card UID matches the expected value
  if (cardUid == "63855195") {  // Replace with the actual card UID you want to match
    Serial.println("Card ID Verified");

    // Write totalCoins to the RFID card
    byte dataBuffer[BLOCK_SIZE];
    memset(dataBuffer, 0, BLOCK_SIZE); // Clear the buffer

    // Convert totalCoins to bytes
    memcpy(dataBuffer, &totalCoins, sizeof(totalCoins));

    // Write the data buffer to the card
    for (byte i = 0; i < BLOCK_SIZE; i++) {
      mfrc522.MIFARE_Write(i, &dataBuffer[i], 1);
    }

    Serial.print("Total Coins Written to Card: ");
    Serial.println(totalCoins);
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

  // Check if the card UID matches the expected value
  if (cardUid == "63855195") {  // Replace with the actual card UID you want to match
    Serial.println("Card ID Verified");

    // Read totalCoins from the RFID card
    byte dataBuffer[BLOCK_SIZE];
    memset(dataBuffer, 0, BLOCK_SIZE); // Clear the buffer

    // Read the data buffer from the card
    for (byte i = 0; i < BLOCK_SIZE; i++) {
      mfrc522.MIFARE_Read(i, &dataBuffer[i], 1);
    }

    // Convert bytes back to totalCoins
    float totalCoinsRead;
    memcpy(&totalCoinsRead, dataBuffer, sizeof(totalCoinsRead));

    Serial.print("Total Coins Read from Card: ");
    Serial.println(totalCoinsRead);

    // Display the totalCoins on the LCD
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Total Coins:");
    lcd.setCursor(2, 1);
    lcd.print(totalCoinsRead);
    delay(5000);  // Display for 5 seconds
    lcd.clear();
  }
}
