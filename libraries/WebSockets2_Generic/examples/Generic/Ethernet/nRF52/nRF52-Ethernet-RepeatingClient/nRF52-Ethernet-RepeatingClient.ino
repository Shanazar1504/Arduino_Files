/****************************************************************************************************************************
  nRF52-Ethernet-RepeatingClient.ino
  For nRF52 with Ethernet module/shield.
  
  Based on and modified from Gil Maimon's ArduinoWebsockets library https://github.com/gilmaimon/ArduinoWebsockets
  to support STM32F/L/H/G/WB/MP1, nRF52 and SAMD21/SAMD51 boards besides ESP8266 and ESP32


  The library provides simple and easy interface for websockets (Client and Server).
  
  Built by Khoi Hoang https://github.com/khoih-prog/Websockets2_Generic
  Licensed under MIT license       
 *****************************************************************************************************************************/
/****************************************************************************************************************************
	nRF52 Websockets Repeating Client

 This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Sends the websockets server a message ("Hello to Server from ......")
        4. Prints all incoming messages while the connection is open
        5. Repeat 2-4 every REPEAT_INTERVAL (10 seconds)

	Hardware:
        For this sketch you only need an nRF52 board.

	Originally Created  : 15/02/2019
	Original Author     : By Gil Maimon
	Original Repository : https://github.com/gilmaimon/ArduinoWebsockets

*****************************************************************************************************************************/

#include "defines.h"

#include <WebSockets2_Generic.h>

using namespace websockets2_generic;

WebsocketsClient client;

// Select the IP address according to your local network
IPAddress serverIP(192, 168, 2, 30);

const char* websockets_server_host = "192.168.2.30"; //Enter server address
//const char* websockets_server_host = "serverip_or_name"; //Enter server address

#define WEBSOCKETS_PORT   8080

const uint16_t websockets_server_port = WEBSOCKETS_PORT; // Enter server port

void onEventsCallback(WebsocketsEvent event, String data) 
{
  (void) data;
  
  if (event == WebsocketsEvent::ConnectionOpened) 
  {
    Serial.println("Connnection Opened");
  } 
  else if (event == WebsocketsEvent::ConnectionClosed) 
  {
    Serial.println("Connnection Closed");
  } 
  else if (event == WebsocketsEvent::GotPing) 
  {
    Serial.println("Got a Ping!");
  } 
  else if (event == WebsocketsEvent::GotPong) 
  {
    Serial.println("Got a Pong!");
  }
}

void initEthernet()
{
#if USE_ETHERNET_GENERIC
  LOGWARN(F("=========== USE_ETHERNET_GENERIC ==========="));  
#elif USE_ETHERNET_ESP8266
  LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
#elif USE_ETHERNET_ENC
  LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));  
#else
  LOGWARN(F("========================="));
#endif

#if (USING_SPI2)
  #if defined(CUR_PIN_MISO)
    LOGWARN(F("Default SPI pinout:"));
    LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
    LOGWARN1(F("MISO:"), CUR_PIN_MISO);
    LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
    LOGWARN1(F("SS:"),   CUR_PIN_SS);
    LOGWARN(F("========================="));
  #endif
#else
  LOGWARN(F("Default SPI pinout:"));
  LOGWARN1(F("MOSI:"), MOSI);
  LOGWARN1(F("MISO:"), MISO);
  LOGWARN1(F("SCK:"),  SCK);
  LOGWARN1(F("SS:"),   SS);
  LOGWARN(F("========================="));
#endif

  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);
  
  LOGWARN2(BOARD_NAME, F(" setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    // Default pin 5/17 to SS/CS
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
     
  #endif    //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

  LOGWARN(F("========================="));
  
  #if defined(CUR_PIN_MISO)
    LOGWARN(F("Currently Used SPI pinout:"));
    LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
    LOGWARN1(F("MISO:"), CUR_PIN_MISO);
    LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
    LOGWARN1(F("SS:"),   CUR_PIN_SS);
  #else
    LOGWARN(F("Currently Used SPI pinout:"));
    LOGWARN1(F("MOSI:"), MOSI);
    LOGWARN1(F("MISO:"), MISO);
    LOGWARN1(F("SCK:"),  SCK);
    LOGWARN1(F("SS:"),   SS);
  #endif
  
  LOGWARN(F("========================="));
}

void setup()
{
#if (defined(ETHERNET_WITH_SD_CARD) && ETHERNET_WITH_SD_CARD)
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
#endif

  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  Serial.println("\nStarting nRF52-Ethernet-RepeatingClient on " + String(BOARD_NAME));
  Serial.println("Ethernet using " + String(ETHERNET_TYPE));
  Serial.println(WEBSOCKETS2_GENERIC_VERSION);

  initEthernet();

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], clientIP);
  Ethernet.begin(mac[index]);

  Serial.print("WebSockets Client IP address: ");
  Serial.println(Ethernet.localIP());

  Serial.print("Connecting to WebSockets Server @");
  Serial.println(websockets_server_host);

  // run callback when messages are received
  client.onMessage([&](WebsocketsMessage message)
  {
    Serial.print("Got Message: ");
    Serial.println(message.data());
  });

  // run callback when events are occuring
  client.onEvent(onEventsCallback);
}

void sendMessage(void)
{
// try to connect to Websockets server
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
  
  if (connected) 
  {
    Serial.println("Connected!");

    String WS_msg = String("Hello to Server from ") + BOARD_NAME;
    client.send(WS_msg);
  } 
  else 
  {
    Serial.println("Not Connected!");
  }
}

void checkToSendMessage()
{
  #define REPEAT_INTERVAL    10000L
  
  static unsigned long checkstatus_timeout = 0;

  // Send WebSockets message every REPEAT_INTERVAL (10) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    sendMessage();
    checkstatus_timeout = millis() + REPEAT_INTERVAL;
  }
}

void loop() 
{

  checkToSendMessage();
  
  // let the websockets client check for incoming messages
  if (client.available()) 
  {
    client.poll();
  }
}
