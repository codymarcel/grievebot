using namespace std;

#define BUF_SIZE 512

long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
#if 0
  int port = 3000;
  IPAddress server(192,168,0,189); // Local
#else
  char server[] = "grievebot.heroku.com";
  int port = 80;
#endif

EthernetClient client;
int crlf = 0;
int sr = 0;
int sn = 0;

char message[BUF_SIZE]="x term innaate";
int message_index = 0;

boolean is_new_packet = true;
boolean read_header = false;


void new_request() {

  client.println("GET /chatter_feed/feed HTTP/1.1");
  client.println("Host: grievebot.heroku.com"); 
  client.println("User-Agent: Arduino (Arduino Test Code)");
  client.println();
  
  is_new_packet = false;
}
void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.print("Connecting to server: ");
  Serial.print(server);
  Serial.print(" : ");
  Serial.println(port);
  
  if (client.connect(server, port)) {
    new_request();
    //Serial.println("Sent request");
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}   

void zeroBuffer(char * message, int len){
  for (int i=0; i<len; i++) {
    message[i] = '\0';
  }
}

void reset_network_status() {
  is_new_packet = true;
  read_header = false;
  zeroBuffer(message, BUF_SIZE);
  message_index = 0;
}

void speak_msg(){
  char c;
  String s;
  int i = 1;
  
  while(client.available()){
    c = client.read();
    
    //Serial.print(c);
    s.concat(c);
    i++;
  }
  
  char msg[i];
  s.toCharArray(msg, i);
  speak(msg);
}

void parse_message(){
  char c;
   if (client.available()) {
    c = client.read();
    if ((c == '\r')){
      Serial.print(c);
      c = client.read();
      if(c == '\n'){
        Serial.print(c);
        
        if(++crlf == 2){
          //Serial.println("\nFound header end.\n");
          speak_msg();
        }
        return;
      }
    }
    crlf = 0;
    // Prints the raw header response
    // Serial.print(c);
   }  
}


/*
void parse_message(){
  char c;
   if (client.available()) {
    c = client.read();
    if ((c == '\r')){
      Serial.print(c);
      c = client.read();
      if(c == '\n'){
        Serial.print(c);
        
        if(++crlf == 2){
          //Serial.println("\nFound header end.\n");
          speak_msg();
        }
        return;
      }
    }
    crlf = 0;
    // Prints the raw header response
    // Serial.print(c);
   }  
}
*/
