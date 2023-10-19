#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "Sanly_Saglyk";
const char* password = "000000001";

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

#define RST_PIN    D3    // Reset pin
#define SS_PIN     D8    // Slave Select pin

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create instance of the MFRC522 RFID reader

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.137.1/sanly_saglyk/rfidapi.php?rfid=";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  SPI.begin();       // Initialize SPI communication
  mfrc522.PCD_Init();   // Initialize MFRC522
  lcd.begin();
  lcd.backlight();

  Serial.println("Ready to read RFID card...");

}

void loop() {

  getRFID();
  Print_lcd();
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

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(" Ustunlikli!!!");
  delay(1500);
  lcd.clear();


  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String serverPath = serverName + cardUid ;

    Serial.println(serverPath);

    // Your Domain name with URL path or IP address with path
    http.begin(client, serverPath.c_str());

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();

  }
}

void Print_lcd() {
  lcd.setCursor(5, 0);
  lcd.print("Girisi");
  lcd.setCursor(2, 1);
  lcd.print("amala asyryn");
}
