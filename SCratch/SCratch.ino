//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include "MemoryFree.h"
#include "pmem.h"
//#include <PinChangeInt.h>
//#include <PinChangeIntConfig.h>
#include "speak.h"
#include "net_util.h"

#define LED_PIN 9
#define BUTTON_PIN 6
#define PROXIMITY_PIN A0 
#define DISTANCE_THRESHOLD 100000


void setup()
{
  //Set up a serial port to get the ascii message from the host
  Serial.begin(9600);
  delay(1500);
  String server;
  String s;
  
  server = "grievebot.heroku.com";
  char arr[] = "hello";
  
  EEPROM_writeAnything(0, server);  
  EEPROM_readAnything(0, s);
  
  Serial.println(s);
  
  server = "bla.com";
  EEPROM_writeAnything(0, server);  
  EEPROM_readAnything(0, s);
  
  Serial.println(s);
  Serial.println(arr);
  
}

void loop()
{
}


