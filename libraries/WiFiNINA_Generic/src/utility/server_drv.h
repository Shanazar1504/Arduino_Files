/**********************************************************************************************************************************
  server_drv.h - Library for Arduino WiFiNINA module/shield.

  Based on and modified from WiFiNINA library https://www.arduino.cc/en/Reference/WiFiNINA
  to support nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, Teensy, etc. boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR400, etc.
  
  Built by Khoi Hoang https://github.com/khoih-prog/WiFiNINA_Generic
  Licensed under MIT license

  Copyright (c) 2018 Arduino SA. All rights reserved.
  Copyright (c) 2011-2014 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Version: 1.8.14-6

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.5.0      K Hoang    27/03/2020 Initial coding to support other boards besides Nano-33 IoT, MKRWIFI1010, MKRVIDOR4000, etc.
                                   such as Arduino Mega, Teensy, SAMD21, SAMD51, STM32, etc
  ...
  1.8.13     K Hoang    03/08/2021 Sync with WiFiNINA v1.8.13 : new FW v1.4.8. Add support to ADAFRUIT_MATRIXPORTAL_M4_EXPRESS
  1.8.14-1   K Hoang    25/11/2021 Fix examples to support ATmega4809 such as UNO_WIFI_REV2 and NANO_EVERY
  1.8.14-2   K Hoang    31/12/2021 Add support to Nano_RP2040_Connect using arduino-pico core
  1.8.14-3   K Hoang    31/12/2021 Fix issue with UDP for Nano_RP2040_Connect using arduino-pico core
  1.8.14-4   K Hoang    01/05/2022 Fix bugs by using some PRs from original WiFiNINA. Add WiFiMulti-related examples
  1.8.14-5   K Hoang    23/05/2022 Fix bug causing data lost when sending large files
  1.8.14-6   K Hoang    17/08/2022 Add support to Teensy 4.x using WiFiNINA AirLift. Fix minor bug
 ***********************************************************************************************************************************/

#pragma once

#include <inttypes.h>
#include "utility/wifi_spi.h"

// From v1.8.0
typedef enum eProtMode {TCP_MODE, UDP_MODE, TLS_MODE, UDP_MULTICAST_MODE, TLS_BEARSSL_MODE}tProtMode;
//////

class ServerDrv
{
  public:

    // Start server TCP on port specified
    static void startServer(uint16_t port, uint8_t sock, uint8_t protMode = TCP_MODE);

    static void startServer(uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode = TCP_MODE);

    static void startClient(uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode = TCP_MODE);

    static void startClient(const char* host, uint8_t host_len, uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode = TCP_MODE);

    static void stopClient(uint8_t sock);

    static uint8_t getServerState(uint8_t sock);

    static uint8_t getClientState(uint8_t sock);

    static bool getData(uint8_t sock, uint8_t *data, uint8_t peek = 0);

    static bool getDataBuf(uint8_t sock, uint8_t *data, uint16_t *len);

    static bool insertDataBuf(uint8_t sock, const uint8_t *_data, uint16_t _dataLen);

    static uint16_t sendData(uint8_t sock, const uint8_t *data, uint16_t len);

    static bool sendUdpData(uint8_t sock);

    static uint16_t availData(uint8_t sock);
    
    // From https://github.com/arduino-libraries/WiFiNINA/pull/204
    //static uint8_t availServer(uint8_t sock);
    static uint8_t availServer(uint8_t sock, uint8_t accept = false);

    static uint8_t checkDataSent(uint8_t sock);

    static uint8_t getSocket();
};

extern ServerDrv serverDrv;

