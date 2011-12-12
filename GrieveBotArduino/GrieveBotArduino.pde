
//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetDHCP.h>
#include "dns.h"
#include "speak.h"


int wt = 5000;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 134 };
byte server[] = { 74,125,224,115 }; // Google
Client client(server, 80);


//Create a message buffer to hold the ascii message to be converted to sound
char message[128]="Number 5 is al i ve!";

void setup()
{


  //Set up a serial port to get the ascii message from the host
  Serial.begin(9600);
  delay(20000);
  
  Serial.println("Attempting to obtain a DHCP lease...");
  
  // Initiate a DHCP session. The argument is the MAC (hardware) address that
  // you want your Ethernet shield to use. This call will block until a DHCP
  // lease has been obtained. The request will be periodically resent until
  // a lease is granted, but if there is no DHCP server on the network or if
  // the server fails to respond, this call will block forever.
  // Thus, you can alternatively use polling mode to check whether a DHCP
  // lease has been obtained, so that you can react if the server does not
  // respond (see the PollingDHCP example).
  EthernetDHCP.begin(mac);

  // Since we're here, it means that we now have a DHCP lease, so we print
  // out some information.
  const byte* ipAddr = EthernetDHCP.ipAddress();
  const byte* gatewayAddr = EthernetDHCP.gatewayIpAddress();
  const byte* dnsAddr = EthernetDHCP.dnsIpAddress();

  
  speakjet_init();

  speak(message);  
  speak("A  D H C P lease has been obtained.");
  speak("My I P is ");
  speak(ip_to_str(ipAddr));


/*
  if (client.connect()) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
*/  
}

void loop()
{

/*
  if (client.available()) {
    //Serial.println("connected");
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
*/  
  
  // You should periodically call this method in your loop(): It will allow
  // the DHCP library to maintain your DHCP lease, which means that it will
  // periodically renew the lease and rebind if the lease cannot be renewed.
  // Thus, unless you call this somewhere in your loop, your DHCP lease might
  // expire, which you probably do not want :-)
  EthernetDHCP.maintain();
}
