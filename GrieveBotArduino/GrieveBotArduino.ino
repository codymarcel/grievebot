
//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include "dns.h"
#include "speak.h"

long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
int port = 3000;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 134);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 0, 0);

//byte server[] = "www.google.com";
IPAddress server(192,168,0,189); // Local



//Create a message buffer to hold the ascii message to be converted to sound
char message[128]="Number 5 is al i ve!";
EthernetClient client;

void setup()
{
  //Set up a serial port to get the ascii message from the host
  Serial.begin(9600);
  speakjet_init();
  
  speak(message);  
  speak("Trying to get an IP address using DHCP");
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);
  }
  speak("My IP address");
  ip = Ethernet.localIP();
  
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();


  connectToServer();
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
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

}


void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.println("connecting to server...");
  if (client.connect(server, port)) {
    Serial.println("making HTTP request...");
  // make HTTP GET request to twitter:
  /*
    client.println("GET /1/statuses/user_timeline.xml?screen_name=arduino&count=1 HTTP/1.1");
    client.println("HOST: api.twitter.com");
    client.println();
  */
//    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("GET / HTTP/1.1");
    client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}   
