#include <MFRC522.h>  // Include the MFRC522 RFID library

#define RST_PIN D3    // Define the RST_PIN for the RFID module
#define SS_PIN D4     // Define the SS_PIN for the RFID module

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();         // Initialize SPI bus
  mfrc522.PCD_Init();  // Initialize MFRC522 RFID reader
  Serial.println("Ready to read RFID cards");
}

void loop() {
  // Check if a new card is detected
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Get the UID of the card
    String cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }
   
    // Print the UID of the card
    Serial.println("Card UID: " + cardUID);
   
    mfrc522.PICC_HaltA();  // Halt the card
    mfrc522.PCD_StopCrypto1();  // Stop encryption
  }
}
