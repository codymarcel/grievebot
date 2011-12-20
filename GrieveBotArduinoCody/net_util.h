using namespace std;

#define BUF_SIZE 512

long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
#if 1
  int port = 3000;
  IPAddress server(192,168,0,189); // Local
#else
  char server[] = "grievebot.heroku.com";
  int port = 80;
#endif

int serverPort = 1337;
int crlf = 0;
int sr = 0;
int sn = 0;
EthernetServer localServer(serverPort);
EthernetClient client;

char message[BUF_SIZE]="x term in naate";
int message_index = 0;

/*
boolean is_new_packet = true;
boolean read_header = false;
*/

void new_request() {

  Serial.println("Sending request");
  client.println("GET /chatter_feed/feed HTTP/1.1");
  client.println("Host: grievebot.heroku.com"); 
  client.println("User-Agent: Arduino (Arduino Test Code)");
  client.println("");
  Serial.println("Sent request");
  
//  is_new_packet = false;
}
void connectToServer() {
  
  // attempt to connect, and wait a millisecond:
  Serial.print("Connecting to server: ");
  Serial.print(server);
  Serial.print(" : ");
  Serial.println(port);
  
  if (client.connect(server, port)) {
    new_request();
  } else{
    Serial.println("Stopping...");
    client.flush();
    client.stop();
  }
    
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}   

void zeroBuffer(char * message, int len){
  for (int i=0; i<len; i++) {
    message[i] = '\0';
  }
}

/*
void reset_network_status() {
  is_new_packet = true;
  read_header = false;
  zeroBuffer(message, BUF_SIZE);
  message_index = 0;
}
*/

char* get_message(){
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
  return msg;
}

void parse_header(){
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
          //speak_msg();
          return;
        }
        return;
      }
    }
    crlf = 0;
    // Prints the raw header response
    // Serial.print(c);
   }  
}

void parse_message(){
  parse_header();
  char* msg = get_message();
  speak(msg);
  client.stop();
}

void server_listener(){
  // listen for incoming clients
  EthernetClient localClient = localServer.available();
  if (localClient) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (localClient.connected()) {
      if (localClient.available()) {
        char c = localClient.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          localClient.println("HTTP/1.1 200 OK");
          localClient.println("Content-Type: text/html");
          localClient.println("SPEAKING");
          localClient.println();
          
          speak(get_message());
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    localClient.stop();
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
