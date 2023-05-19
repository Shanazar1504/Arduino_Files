// Include the VirtualWire library for RF communication
#include <VirtualWire.h>

// Define the RF module pins
#define RX_PIN 11 // Pin to receive data
#define LED1_PIN 13 // Pin to control LED1
#define LED2_PIN 10 // Pin to control LED2

void setup() {
  // Initialize the Serial communication
  Serial.begin(9600);
  
  // Initialize the RF module
  vw_set_rx_pin(RX_PIN);
  vw_setup(2000);  // Bits per sec
  vw_rx_start(); // Start RF reception
  pinMode(LED1_PIN, OUTPUT); // Initialize LED1 pin
  pinMode(LED2_PIN, OUTPUT); // Initialize LED2 pin
}

void loop() {
  char command;
  uint8_t commandSize = sizeof(command);
  
  // Check for RF reception
  if (vw_get_message((uint8_t *)&command, &commandSize)) {
    // Control the LEDs based on the received command
    switch (command) {
      case COMMAND_LED1_ON:
        digitalWrite(LED1_PIN, HIGH);
        break;
      case COMMAND_LED1_OFF:
        digitalWrite(LED1_PIN, LOW);
        break;
      case COMMAND_LED2_ON:
        digitalWrite(LED2_PIN, HIGH);
        break;
      case COMMAND_LED2_OFF:
        digitalWrite(LED2_PIN, LOW);
        break;
      default:
        // Invalid command received
        break;
    }
  }
}
