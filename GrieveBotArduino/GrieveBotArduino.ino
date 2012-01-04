//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "speak.h"
#include "net_util.h"

#define BUTTON_PIN 6
#define PROXIMITY_PIN A0 
#define DISTANCE_THRESHOLD 100000

//long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
//int port = 3000;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 134);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 0, 0);

//IPAddress server(192,168,0,189); // Local

//Create a message buffer to hold the ascii message to be converted to sound

//EthernetClient client; 
//char message[BUF_SIZE]="x term in naate";
String message = "x term in naate";
String post_liked = "This post is worthy of grieve bot";
String post_was_liked = "grieve bot already likes this";

int message_index = 0;
volatile boolean isLiked = 0;

void setup()
{
  //Set up a serial port to get the ascii message from the host
  Serial.begin(9600);
  delay(1000);
  speakjet_init();
  
  speak(message);
  
 
  Serial.println("Trying to get an I P address using D H C P");
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using D H C P");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);
  }
  ip = Ethernet.localIP();
  //speak(ip_to_str(ip));
  //connectToServer();
  
  // Attach an interrupt to pin 6 using the PCinPort library
  // This allows us to use non-standard arduino pins as interrupts
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
  PCintPort::attachInterrupt(BUTTON_PIN, enableLike, RISING);
  
  // Set up proximity sensor pin
  pinMode(PROXIMITY_PIN, INPUT);

}


// Interrupt handler for like button
void enableLike(){
  isLiked=true;
}


boolean gotMessage = false;     // indicate that a message was recieved from the server
boolean ready_for_like = false; // indicate that we have parsed a post (for like button)
int ct = 0;
void loop()
{
  // Read our proxmity sensor
  int  reading = analogRead(PROXIMITY_PIN);
  delay(200);
  
  // Don't go on unless someone is nearby
  if (reading < DISTANCE_THRESHOLD) {
    return;
  }
  
  connectToServer("GET");
  if(client.available()){ 
    parse_message();
    delay(5000);
    ready_for_like = true;
    gotMessage = true;
    //server_listener();
  }
    
  // Stop it from spamming requests and hitting the API request limit
  if(gotMessage){
    ct++;
    gotMessage = false;
    String s = String("disconnecting.");
    speak(s);
    client.flush();
    client.stop();
    
    // wait 10
    delay(10000);
    
    // only do 3 requests
    if(ct >= 3){
      while(1){
      }
    }
  }
  
  // if the like interrupt was triggered then
  // check if we have a post and like it
  if (isLiked && ready_for_like) {
    if (is_already_liked) { // We've already seen this post
      Serial.println(post_was_liked);
    } else {
      Serial.println(post_liked);
      connectToServer("POST"); // Send the like command
      delay(500);
    }
    isLiked=false;
  }

  /*
  if(gotMessage){
    Serial.println("disconnecting.");
    client.stop();
    connectToServer("POST");
    gotMessage = false;
    liked = true;  
  }

  */
}

