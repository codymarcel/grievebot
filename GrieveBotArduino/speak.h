//Define the Pin Numbers of the Voicebox shield for the sketch.
/*
#define E0  5
#define E1  6
#define E2  7
#define E3  8
#define E4  9
#define E5  10
#define E6  11
#define E7  12
*/

#define RDY  5
#define RES  3
#define SPK  4

//Pin 2 of the shield should be wired to the TTS256 chip.
#define txPin  2

//Create a SoftSerial Object to send strings to the TTS256 chip.
SoftwareSerial speakjet = SoftwareSerial(0, txPin);

void speakjet_init(){
   //Configure the pins for the SpeakJet module
  pinMode(txPin, OUTPUT);
  pinMode(SPK, INPUT);
  
  //Set up a serial port to talk from Arduino to the SpeakJet module on pin 3.
  speakjet.begin(9600);    
    
  //Configure the Ready pin as an input
  pinMode(RDY, INPUT);
  
  //Configure Reset line as an output
  pinMode(RES, OUTPUT);
       
  //Configure all of the Event pins as outputs from Arduino, and set them Low.
  /*
  for(int i=E0; i<=E7; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  */
  
  //All I/O pins are configured. Reset the SpeakJet module
  digitalWrite(RES, LOW);
  delay(100);
  digitalWrite(RES, HIGH);
  delay(1000); 
  digitalWrite(13, LOW);
}

void speak(String message){
  Serial.print("\nSpeaking: ");
  Serial.println(message);
  
  speakjet.println(message);
  
  // Wait for it to finish speaking
  delay(20);
  while(digitalRead(SPK)) {
    delay(250);
  }
  delay(250);
}

