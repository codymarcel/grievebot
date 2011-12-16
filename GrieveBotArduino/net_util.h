
using namespace std;

long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
int port = 3000;

EthernetClient client;
IPAddress server(192,168,0,189); // Local
int crlf = 0;
int sr = 0;
int sn = 0;

#define BUF_SIZE 512
char message[BUF_SIZE]="exterminate";
int message_index = 0;

boolean is_new_packet = true;
boolean read_header = false;

void new_request() {
  client.println("GET /chatter_feed/feed HTTP/1.1");
  client.println();
  is_new_packet = false;
}
void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.println("Connecting to server");
  
  if (client.connect(server, port)) {
    new_request();
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
    Serial.print(c);
    s.concat(c);
    i++;
  }
  
  char msg[i];
  s.toCharArray(msg, i);
  speak(msg);
}



