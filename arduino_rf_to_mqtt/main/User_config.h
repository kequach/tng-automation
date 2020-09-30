/*  
  OpenMQTTGateway  - ESP8266 or Arduino program for home automation 

   Act as a wifi or ethernet gateway between your 433mhz/infrared IR signal  and a MQTT broker 
   Send and receiving command by MQTT
 
  This program enables to:
 - receive MQTT data from a topic and send signals corresponding to the received MQTT data
 - publish MQTT data to a different topic related to received signals
  
    Copyright: (c)Florian ROBERT
  
    This file is part of OpenMQTTGateway.
    
    OpenMQTTGateway is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenMQTTGateway is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef user_config_h
#define user_config_h
/*-------------------VERSION----------------------*/
#ifndef OMG_VERSION
#  define OMG_VERSION "v0.9.5"
#endif
#ifndef ESPWifiManualSetup
#  define ESPWifiManualSetup true
#endif
#ifndef ZgatewayRFCC1101
#  define ZgatewayRFCC1101
#endif

/*-------------CONFIGURE WIFIMANAGER-------------(only ESP8266 & SONOFF RFBridge)*/
/*
 * The following parameters are set during the WifiManager setup process:
 * - wifi_ssid
 * - wifi_password
 * - mqtt_user
 * - mqtt_pass
 * - mqtt_server
 * - mqtt_port
 * 
 * To completely disable WifiManager, define ESPWifiManualSetup.
 * If you do so, please don't forget to set these variables before compiling
 * 
 * Otherwise you can provide these credentials on the web interface after connecting 
 * to the access point with your password (SSID: WifiManager_ssid, password: WifiManager_password)
 */
/*-------------DEFINE GATEWAY NAME BELOW IT CAN ALSO BE DEFINED IN platformio.ini----------------*/
#ifndef Gateway_Name
#  define Gateway_Name "OpenMQTTGateway"
#endif
#ifndef Gateway_Short_Name
#  define Gateway_Short_Name "OMG"
#endif

#ifndef Base_Topic
#  define Base_Topic "home/"
#endif

/*-------------DEFINE YOUR NETWORK PARAMETERS BELOW----------------*/

//#define NetworkAdvancedSetup true //uncomment if you want to set advanced network parameters for arduino boards, not uncommented you can set the IP and mac only
#ifdef NetworkAdvancedSetup // for arduino boards advanced config
#  if defined(ESP8266) || defined(ESP32)
const byte ip[] = {192, 168, 1, 99}; //ip adress of the gateway, already defined for arduino below
#  endif
const byte gateway[] = {0, 0, 0, 0};
const byte Dns[] = {0, 0, 0, 0};
const byte subnet[] = {255, 255, 255, 0};
#endif

#if defined(ESP8266) || defined(ESP32) // for nodemcu, weemos and esp8266
//#  define ESPWifiManualSetup true //uncomment you don't want to use wifimanager for your credential settings on ESP
#else // for arduino boards
const byte ip[] = {192, 168, 1, 99};
const byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0x54, 0x95}; //W5100 ethernet shield mac adress
#endif

//#define ESP32_ETHERNET=true // Uncomment to use Ethernet module on OLIMEX ESP32 Ethernet gateway

#if defined(ESPWifiManualSetup) // for nodemcu, weemos and esp8266
#  ifndef wifi_ssid
#    define wifi_ssid "ENTER WIFI SSID HERE"
#  endif
#  ifndef wifi_password
#    define wifi_password "ENTER PASSWORD HERE"
#  endif
#endif

/*-------------DEFINE YOUR ADVANCED NETWORK PARAMETERS BELOW----------------*/
//#define MDNS_SD //uncomment if you  want to use mdns for discovering automatically your ip server, please note that MDNS with ESP32 can cause the BLE to not work
#define maxConnectionRetry     10 //maximum MQTT connection attempts before going to wifimanager setup if never connected once
#define maxConnectionRetryWifi 5 //maximum Wifi connection attempts with existing credential at start (used to bypass ESP32 issue on wifi connect)

//set minimum quality of signal so it ignores AP's under that quality
#define MinimumWifiSignalQuality 8

/*-------------DEFINE YOUR MQTT PARAMETERS BELOW----------------*/
//MQTT Parameters definition
#define parameters_size      30
#define mqtt_topic_max_size  100
#define mqtt_max_packet_size 1024

#ifndef MQTT_USER
#  define MQTT_USER "your_username"
#endif
#ifndef MQTT_PASS
#  define MQTT_PASS "your_password"
#endif
#ifndef MQTT_SERVER
#  define MQTT_SERVER "ENTER MQTT BROKER IP ADRESS HERE"
#endif
#ifndef MQTT_PORT
#  define MQTT_PORT "1883"
#endif

#define ATTEMPTS_BEFORE_BG 10 // Number of wifi connection attempts before going to BG protocol
#define ATTEMPTS_BEFORE_B  20 // Number of wifi connection attempts before going to B protocol

/*------------------DEEP SLEEP parameters ------------------*/

// WIFI mode, uncomment to force a wifi mode, if not uncommented the ESP will connect without a mode forced
// if there is a reconnection issue it will try to connect with G mode and if not working with B mode



/*-------------DEFINE THE MODULES YOU WANT BELOW----------------*/
//Addons and module management, uncomment the Z line corresponding to the module you want to use

//#define ZgatewayRF     "RF"       //ESP8266, Arduino, ESP32

/*-------------DEFINE YOUR MQTT ADVANCED PARAMETERS BELOW----------------*/
#ifndef version_Topic
#  define version_Topic "/version"
#endif
#ifndef will_Topic
#  define will_Topic "/LWT"
#endif
#ifndef will_QoS
#  define will_QoS 0
#endif
#ifndef will_Retain
#  define will_Retain true
#endif
#ifndef will_Message
#  define will_Message "offline"
#endif
#ifndef Gateway_AnnouncementMsg
#  define Gateway_AnnouncementMsg "online"
#endif

#ifndef jsonPublishing
#  define jsonPublishing true //comment if you don't want to use Json  publishing  (one topic for all the parameters)
#endif
//example home/OpenMQTTGateway_ESP32_DEVKIT/BTtoMQTT/4XXXXXXXXXX4 {"rssi":-63,"servicedata":"fe0000000000000000000000000000000000000000"}
#ifndef jsonReceiving
#  define jsonReceiving true //comment if you don't want to use Json  reception analysis
#endif

//#define simplePublishing true //comment if you don't want to use simple publishing (one topic for one parameter)
//example
// home/OpenMQTTGateway_ESP32_DEVKIT/BTtoMQTT/4XXXXXXXXXX4/rssi -63.0
// home/OpenMQTTGateway_ESP32_DEVKIT/BTtoMQTT/4XXXXXXXXXX4/servicedata fe0000000000000000000000000000000000000000
//#define simpleReceiving true //comment if you don't want to use old way reception analysis

/*-------------DEFINE YOUR OTA PARAMETERS BELOW----------------*/
#ifndef ota_hostname
#  define ota_hostname Gateway_Name
#endif
#ifndef ota_password
#  define ota_password "OTAPASSWORD"
#endif
#ifndef ota_port
#  define ota_port 8266
#endif

/*-------------DEFINE PINs FOR STATUS LEDs----------------*/
#ifndef LED_RECEIVE
#  define LED_RECEIVE 40
#endif
#ifndef LED_RECEIVE_ON
#  define LED_RECEIVE_ON HIGH
#endif
#ifndef LED_SEND
#  define LED_SEND 42
#endif
#ifndef LED_SEND_ON
#  define LED_SEND_ON HIGH
#endif
#ifndef LED_INFO
#  define LED_INFO 44
#endif
#ifndef LED_INFO_ON
#  define LED_INFO_ON HIGH
#endif

#ifdef ESP8266
//#  define TRIGGER_GPIO 14 // pin D5 as full reset button (long press >10s)
#endif

//      VCC   ------------D|-----------/\/\/\/\ -----------------  Arduino PIN
//                        LED       Resistor 270-510R

/*----------------------------OTHER PARAMETERS-----------------------------*/
/*-------------------CHANGING THEM IS NOT COMPULSORY-----------------------*/
/*----------------------------USER PARAMETERS-----------------------------*/
#define SERIAL_BAUD 115200
/*--------------MQTT general topics-----------------*/
// global MQTT subject listened by the gateway to execute commands (send RF, IR or others)
#define subjectMQTTtoX     "/commands/#"
#define subjectMultiGTWKey "toMQTT"
#define subjectGTWSendKey  "MQTTto"

// key used for launching commands to the gateway
#define restartCmd "restart"
#define eraseCmd   "erase"

// uncomment the line below to integrate msg value into the subject when receiving
//#define valueAsASubject true

#if defined(ESP8266) || defined(ESP32)
#  define JSON_MSG_BUFFER    512 // Json message max buffer size, don't put 1024 or higher it is causing unexpected behaviour on ESP8266
#  define SIGNAL_SIZE_UL_ULL uint64_t
#  define STRTO_UL_ULL       strtoull
#elif defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
#  define JSON_MSG_BUFFER    512 // Json message max buffer size, don't put 1024 or higher it is causing unexpected behaviour on ESP8266
#  define SIGNAL_SIZE_UL_ULL uint64_t
#  define STRTO_UL_ULL       strtoul
#else // boards with smaller memory
#  define JSON_MSG_BUFFER    64 // Json message max buffer size, don't put 1024 or higher it is causing unexpected behaviour on ESP8266
#  define SIGNAL_SIZE_UL_ULL uint32_t
#  define STRTO_UL_ULL       strtoul
#endif

#if defined(ZgatewayRF) || defined(ZgatewayIR) || defined(ZgatewaySRFB) || defined(ZgatewaySRFB) || defined(ZgatewayWeatherStation)
// variable to avoid duplicates
#  define time_avoid_duplicate 3000 // if you want to avoid duplicate mqtt message received set this to > 0, the value is the time in milliseconds during which we don't publish duplicates
#endif

#define TimeBetweenReadingSYS        120 // time between (s) system readings (like memory)
#define TimeLedON                    0.5 // time LED are ON
#define InitialMQTTConnectionTimeout 10 // time estimated (s) before the board is connected to MQTT
#define subjectSYStoMQTT             "/SYStoMQTT"
#define subjectMQTTtoSYSset          "/commands/MQTTtoSYS/config"

/*-------------------DEFINE LOG LEVEL----------------------*/
#define LOG_LEVEL LOG_LEVEL_NOTICE

#endif
