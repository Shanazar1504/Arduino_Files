#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial bluetoothSerial(2, 3); // RX, TX for Bluetooth module

const int gasPin = 4;     // Pin connected to gas sensor (replace with actual pins)
const int firePin = 6;    // Pin connected to fire sensor (replace with actual pins)
const int buzzer = 11;

struct SensorDataTempHumid {
  float humidity;
  float temperature;
};

struct SensorDataGas {
  int gasValue; // Change data type to int for gas value
};

struct SensorDataFire {
  int fireValue; // Assuming fire value is an integer representing intensity or presence
};

void setup() {
  Serial.begin(9600); // Initialize Serial communication for debugging
  bluetoothSerial.begin(9600); // Initialize Bluetooth serial communication
  dht.begin(); // Initialize the DHT sensor
  pinMode(gasPin, INPUT);
  pinMode(firePin, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  SensorDataTempHumid receivedDataTH;
  receivedDataTH.temperature = dht.readTemperature(); // Replace with actual sensor reading
  receivedDataTH.humidity = dht.readHumidity();    // Replace with actual sensor reading

  // Send temperature and humidity values separately over Bluetooth
  bluetoothSerial.print("T:");
  bluetoothSerial.println(receivedDataTH.temperature);
  bluetoothSerial.print("H:");
  bluetoothSerial.println(receivedDataTH.humidity);

  // Output to serial monitor for debugging
  Serial.print("Received Temperature: ");
  Serial.println(receivedDataTH.temperature);
  Serial.print("Received Humidity: ");
  Serial.println(receivedDataTH.humidity);

  SensorDataGas receivedDataGas;
  receivedDataGas.gasValue = digitalRead(gasPin); // Replace with actual sensor reading

  if (receivedDataGas.gasValue == 0) {
    // Send gas value over Bluetooth
    bluetoothSerial.print("G:");
    bluetoothSerial.println("Howply");
    soundBuzzer();
  } else {
    // Send gas value over Bluetooth
    bluetoothSerial.print("G:");
    bluetoothSerial.println("Kadaly");
    digitalWrite(buzzer, LOW);
  }

  // Output to serial monitor for debugging
  Serial.print("Received Gas Value: ");
  Serial.println(receivedDataGas.gasValue);

  SensorDataFire receivedDataFire;
  receivedDataFire.fireValue = digitalRead(firePin); // Replace with actual sensor reading

  if (receivedDataFire.fireValue == 0) {
    // Send gas value over Bluetooth
    bluetoothSerial.print("F:");
    bluetoothSerial.println("Howply");
    soundBuzzer();
  } else {
    // Send gas value over Bluetooth
    bluetoothSerial.print("F:");
    bluetoothSerial.println("Kadaly");
    digitalWrite(buzzer, LOW);
  }

  // Output to serial monitor for debugging
  Serial.print("Received Fire Value: ");
  Serial.println(receivedDataFire.fireValue);

  delay(500);
}

// Function to sound the buzzer
void soundBuzzer() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
}
