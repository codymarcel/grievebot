
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
char message[128]="Number 5 is alive!";
//EthernetClient client;
boolean foundMessage = false; 
int messageIndex=0;
void setup()
{
  //Set up a serial port to get the ascii message from the host
  Serial.begin(9600);
  speakjet_init();
  
  speak(message);  
  speak("Trying to get an I P address using D H C P");
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using D H C P");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);
  }
  ip = Ethernet.localIP();
  speak(ip_to_str(ip));
    
  connectToServer();
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
    if (c == '~') {
      if (!foundMessage) {
        Serial.println("Found message delimiter start");
        foundMessage = true;
        for (int i=0; i<128; i++) {
          message[i] = '\0';
        }
        return;
      } else {
        speak(message);
        return;
      }    
    }
    
    if (foundMessage) {
        message[messageIndex++] = c;
    }
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }

/*
  delay(20000);
  connectToServer();
*/
}


