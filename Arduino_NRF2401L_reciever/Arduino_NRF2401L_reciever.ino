#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the pipes for communication
const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

RF24 radio(9, 10); // CE, CSN

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
}

void loop() {
  char receivedText[32] = "";

  // Wait for a message
  if (radio.available()) {
    radio.read(&receivedText, sizeof(receivedText));
    Serial.println("Received message: " + String(receivedText));

    // Send a response
    char response[] = "Message received!";
    radio.write(&response, sizeof(response));
  }
}
