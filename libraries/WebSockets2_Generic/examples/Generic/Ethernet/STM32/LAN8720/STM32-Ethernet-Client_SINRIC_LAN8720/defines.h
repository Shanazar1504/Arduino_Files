/****************************************************************************************************************************
  defines.h
  For STM32F/L/H/G/WB/MP1 with Ethernet module/shield.
  
  Based on and modified from Gil Maimon's ArduinoWebsockets library https://github.com/gilmaimon/ArduinoWebsockets
  to support STM32F/L/H/G/WB/MP1, nRF52 and SAMD21/SAMD51 boards besides ESP8266 and ESP32

  The library provides simple and easy interface for websockets (Client and Server).
  
  Built by Khoi Hoang https://github.com/khoih-prog/Websockets2_Generic
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if  ( defined(ARDUINO_BLACK_F407VE) || defined(ARDUINO_BLACK_F407VG) || defined(ARDUINO_BLACK_F407ZE) || defined(ARDUINO_BLACK_F407ZG)     || \
       defined(ARDUINO_BLUE_F407VE_Mini) || defined(ARDUINO_DIYMORE_F407VGT) || defined(ARDUINO_FK407M1) || defined(ARDUINO_NUCLEO_F429ZI)  || \
       defined(ARDUINO_DISCO_F746NG) || defined(ARDUINO_NUCLEO_F746ZG) || defined(ARDUINO_NUCLEO_F756ZG) || defined(ARDUINO_NUCLEO_H743ZI) )
       
  #if defined(WEBSOCKETS_ETHERNET_USE_STM32)
    #undef WEBSOCKETS_ETHERNET_USE_STM32
  #endif
  #define WEBSOCKETS_USE_ETHERNET             true
  #define WEBSOCKETS_ETHERNET_USE_STM32      true
#else
  #error This code is intended to run only on the STM32F/L/H/G/WB/MP1 boards ! Please check your Tools->Board setting.
#endif

#if defined(WEBSOCKETS_ETHERNET_USE_STM32)
  // For STM32
  #if defined(STM32F0)
    #define BOARD_TYPE  "STM32F0"
    #error Board STM32F0 not supported
  #elif defined(STM32F1)
    #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)
    #define BOARD_TYPE  "STM32F7"
  #elif defined(STM32L0)
    #define BOARD_TYPE  "STM32L0"  
  #elif defined(STM32L1)
    #define BOARD_TYPE  "STM32L1"
  #elif defined(STM32L4)
    #define BOARD_TYPE  "STM32L4"
  #elif defined(STM32H7)
    #define BOARD_TYPE  "STM32H7"
  #elif defined(STM32G0)
    #define BOARD_TYPE  "STM32G0"
  #elif defined(STM32G4)
    #define BOARD_TYPE  "STM32G4"
  #elif defined(STM32WB)
    #define BOARD_TYPE  "STM32WB"
  #elif defined(STM32MP1)
    #define BOARD_TYPE  "STM32MP1"  
  #else
    #warning STM32 unknown board selected
    #define BOARD_TYPE  "STM32 Unknown"
  #endif
#endif

#if defined(ARDUINO_BOARD)
  #define BOARD_NAME    ARDUINO_BOARD
#else
  #ifndef BOARD_NAME
    #define BOARD_NAME    BOARD_TYPE
  #endif
#endif

// Just select one to be true. If all is false, default is Ethernet. 
// If more than one are true, the priority is USE_ETHERNET, USE_ETHERNET2, USE_ETHERNET_LARGE, USE_UIP_ETHERNET
#define USING_LAN8720                 true
#define USE_LAN8742A_ETHERNET         false
#define USE_ETHERNET_GENERIC          false
#define USE_ETHERNET_ENC              false
#define USE_UIP_ETHERNET              false

#if ( USE_LAN8742A_ETHERNET  || USING_LAN8720 )
  #define USE_BUILTIN_ETHERNET        true
  #include <LwIP.h>
  #include <STM32Ethernet.h>
  #if USING_LAN8720
    #define ETHERNET_TYPE             "LAN8720 and STM32Ethernet Library"
  #else
    #define ETHERNET_TYPE             "LAN8742A and STM32Ethernet Library"
  #endif
#elif USE_ETHERNET_GENERIC
  // Also default to Ethernet_Generic library
  #include <Ethernet_Generic.h>
  #define ETHERNET_TYPE               "W5x00 and Ethernet_Generic Library"
#elif USE_ETHERNET_ENC
  #include <EthernetENC.h>
  #define ETHERNET_TYPE               "ENC28J60 and EthernetENC Library"  
#elif USE_UIP_ETHERNET
  #include <UIPEthernet.h>
  #include <utility/logging.h> 
  #define ETHERNET_TYPE               "ENC28J60 and UIPEthernet Library" 
#else
  // Default to Ethernet_Generic library
  #include <Ethernet_Generic.h>
  #define ETHERNET_TYPE               "W5x00 and Ethernet_Generic Library"
#endif

#ifndef USE_THIS_SS_PIN
  #define USE_THIS_SS_PIN   10    // For other boards
#endif

#define DEBUG_WEBSOCKETS_PORT     Serial
// Debug Level from 0 to 4
#define _WEBSOCKETS_LOGLEVEL_     3

#if USE_ETHERNET_GENERIC
  // Change to true if using old Ethernet card with built-in SD
  #define ETHERNET_WITH_SD_CARD   false
#endif

#if (defined(ETHERNET_WITH_SD_CARD) && ETHERNET_WITH_SD_CARD)
  #define W5100_CS        10
  #define SDCARD_CS       4
#endif

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

#endif      //defines_h
