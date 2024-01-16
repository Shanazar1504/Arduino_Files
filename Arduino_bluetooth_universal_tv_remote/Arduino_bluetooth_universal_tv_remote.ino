#include <IRremote.h>
#include <SoftwareSerial.h>

// Define IR LED pin
const int IR_LED_PIN = 3; // Connect the IR LED to pin 3

// Define Bluetooth module pins
SoftwareSerial BTserial(4, 5); // RX, TX

// Define button codes to send via IR LED
#define BUTTON_POWER 0xF30C0E0E
#define BUTTON_VOLUME_UP 0xEB140E0E
#define BUTTON_VOLUME_DOWN 0xEA150E0E
#define BUTTON_CHANNEL_UP 0xED120E0E
#define BUTTON_CHANNEL_DOWN 0xEC130E0E
#define BUTTON_MUTE 0xF20D0E0E
#define BUTTON_MENU 0xEE110E0E
#define BUTTON_SOURCE 0xF00F0E0E
#define BUTTON_ENTER 0xB9460E0E
#define BUTTON_UP 0xBD420E0E
#define BUTTON_DOWN 0xBC430E0E
#define BUTTON_LEFT 0xBB440E0E
#define BUTTON_RIGHT 0xBA450E0E
#define BUTTON_EXIT 0xF40B0E0E

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  IrSender.begin(IR_LED_PIN);
}

void loop() {
  // Check for incoming Bluetooth data
  if (BTserial.available() > 0) {
    char command = BTserial.read();
    Serial.println(command);
    executeBluetoothCommand(command);
    
  }
}

void executeBluetoothCommand(char command) {
  // You can implement actions based on the received Bluetooth command
  switch (command) {
    case 'P':
      sendIRCode(BUTTON_POWER);
      break;
    case 'V':
      sendIRCode(BUTTON_VOLUME_UP);
      break;
    case 'D':
      sendIRCode(BUTTON_VOLUME_DOWN);
      break;
    case 'U':
      sendIRCode(BUTTON_CHANNEL_UP);
      break;
    case 'C':
      sendIRCode(BUTTON_CHANNEL_DOWN);
      break;
    case 'M':
      sendIRCode(BUTTON_MUTE);
      break;
    case 'O':
      sendIRCode(BUTTON_MENU);
      break;
    case 'K':
      sendIRCode(BUTTON_ENTER);
      break;
      case 'E':
      sendIRCode(BUTTON_EXIT);
      break;
    case 'A':
      sendIRCode(BUTTON_UP);
      break;
    case 'N':
      sendIRCode(BUTTON_DOWN);
      break;
    case 'L':
      sendIRCode(BUTTON_LEFT);
      break;
    case 'R':
      sendIRCode(BUTTON_RIGHT);
      break;
    // Add more cases for other Bluetooth commands if needed

    default:
      break;
  }
}

void sendIRCode(unsigned long irCode) {
  IrSender.sendNEC(irCode, 32); // Send NEC IR signal, assuming 32-bit protocol
  delay(50); // Delay to avoid sending the same signal rapidly
}
