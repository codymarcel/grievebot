#include <SoftwareSerial.h>
#define RES  3
#define SPK  4
#define txPin 2

//Create a SoftSerial Object to send strings to the TTS256 chip.
SoftwareSerial speakjet = SoftwareSerial(0, txPin);

void speakjet_init(){
   //Configure the pins for the SpeakJet module
  pinMode(txPin, OUTPUT);
  pinMode(SPK, INPUT);
  
  //Set up a serial port to talk from Arduino to the SpeakJet module on pin 3.
  speakjet.begin(9600);    
    
  //Configure the Ready pin as an input
  //pinMode(RDY, INPUT);
  
  //Configure Reset line as an output
  pinMode(RES, OUTPUT);
         
  //All I/O pins are configured. Reset the SpeakJet module
  digitalWrite(RES, LOW);
  delay(100);
  digitalWrite(RES, HIGH);
  delay(1000); 
  //digitalWrite(13, LOW);
}

void speak(String m){
  
  speakjet.flush();
  Serial.print("Speaking: ");
  
  speakjet.println(m);

  // Wait for it to finish speaking
  while(digitalRead(SPK)) {
    delay(300);
  }
  
  delay(300);
  Serial.println(m);
}

void setup()
{
  //Set up a serial port to get the ascii message from the host
  Serial.begin(9600);
  delay(1000);
  speakjet_init();
 
  speak("hello");

}
void loop()
{
  speak("I am the grievebot");
  delay(3000);
  speak("Arduino isn't very good yet");
  delay(5000);
}
