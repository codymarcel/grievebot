
//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include "dns.h"
#include "speak.h"
#include "net_util.h"

//long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
//int port = 3000;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 134);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 0, 0);

//IPAddress server(192,168,0,189); // Local

//Create a message buffer to hold the ascii message to be converted to sound

//EthernetClient client; 
void setup()
{
  //Set up a serial port to get the ascii message from the host
  Serial.begin(9600);
  delay(1000);
  speakjet_init();
  
  speak("Cody");
  Serial.println("Trying to get an I P address using D H C P");
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using D H C P");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);
  }
  ip = Ethernet.localIP();
  //speak(ip_to_str(ip));
  connectToServer();
}


void loop()
{
  char c;
  
  
   if (client.available()) {
    c = client.read();
    if ((c == '\r')){
      Serial.print(c);
      c = client.read();
      if(c == '\n'){
        Serial.print(c);
        
        if(++crlf == 2){
          Serial.println("\nFound header end.\n");
          speak_msg();
        }
        return;
      }
    }
    crlf = 0;
    Serial.print(c);
   }
    

  /*
  if (is_new_packet) {
    new_request();
  } else {
    process_packet();
  }
  */
}

