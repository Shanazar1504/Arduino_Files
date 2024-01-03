#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the pipes for communication
const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

RF24 radio(9, 10); // CE, CSN

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
}

void loop() {
  char text[] = "Hello, World!";
  
  // Send the data
  radio.write(&text, sizeof(text));

  delay(1000); // Wait before sending the next message
}
