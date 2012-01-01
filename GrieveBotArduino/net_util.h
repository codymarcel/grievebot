#define BUF_SIZE 512

// XML STORAGE
String author;
String last_post_url;
String xml_message;
boolean is_liked;

long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
#if 1
  int port = 3000;
  IPAddress server(192,168,0,195); // Local
#else
  char server[] = "grievebot.heroku.com";
  int port = 80;
#endif

int serverPort = 1337;
int sr = 0;
int sn = 0;
EthernetServer localServer(serverPort);
EthernetClient client;


void new_request() {
  client.println("GET /chatter_feed/feed HTTP/1.1");
  client.println("Host: grievebot.heroku.com"); 
  client.println("User-Agent: Arduino (Arduino Test Code)");
  client.println("");
}

// attempt to connect to the remote server
void connectToServer() {
  if (client.connect(server, port)) {    
    Serial.print("Connected to server... ");
    Serial.print(server);
    Serial.print(" : ");
    Serial.println(port);
    Serial.println("Sending request...");
    new_request();
  } else {
//    Serial.println("Stopping...");
//    client.flush();
//    client.stop();
  }
    
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}   

void zeroBuffer(char * message, int len){
  for (int i=0; i<len; i++) {
    message[i] = '\0';
  }
}

// GHETTO PARSER (G-PARSE)
//   matches tag names to global variables
void parse_xml(String &msg){
  String current_tag;
  boolean is_tag = false;
  boolean is_data = false;
  
  // Clear current xml storage
  author = "";
  last_post_url = "";
  xml_message = "";
  
  Serial.println("Starting XML Parse...");
  for (int i=0; i < msg.length(); i++) {
    char c = msg.charAt(i);
    
    // start reading the name of the new tag
    if (c == '<') {
      is_tag = true;
      is_data = false;
      current_tag = "";
      continue;
    }
    
    // read a tag name till the end of that tag
    if (is_tag) { 
      if (c != '>') {
        current_tag.concat(c); 
      } else {
        is_tag = false;
        is_data = true;
        //Serial.print("Found tag: "); Serial.println(current_tag);  
        continue;
      }
    }
    
    // read the data in between tags, save to appropriate variable
    if (is_data) {
      if (current_tag.equals("message")) {
        xml_message.concat(c);
      }
      if (current_tag.equals("author")) {
        author.concat(c);
      }
      if (current_tag.equals("last_post_url")) {
        last_post_url.concat(c);
      }
    }
  }
}

void get_message(String &output){
  char c;
  
  Serial.println("Getting payload...");
  while(client.available()){
    c = client.read();
    output.concat(c);
  }
  output.trim();
  Serial.println(output);
  
}

void parse_header(){
  if(!client.available()){
    Serial.println("Nothing to parse...");
    return;
  }    
 
  int crlf = 0;
  char c;
  Serial.println("Reading header...");
  while (1) {
    if (client.available()) {
      c = client.read();
      
      // This will print the header
      Serial.print(c);

      // Find two \r\n's at the end of the header
      if ((c == '\r')) {
        c = client.read();
        if(c == '\n'){        
          if(++crlf == 2) {
            return;
          } else {
            Serial.println();
          }
        }
      } else {
        crlf = 0;
      }
    }
    delay(1);
  }
}

// Parse bytes from the ethernet client
//   Fast-forward past header
//   Get raw payload (XML from server)
//   Parse out payload into global vars
//   Speak our message
void parse_message(){
  String msg;
  
  parse_header();
  get_message(msg);
  parse_xml(msg);
  
  Serial.print("Author: "); Serial.println(author);
  Serial.print("URL: "); Serial.println(last_post_url);
  Serial.print("Message: "); Serial.println(xml_message);
  
  speak(xml_message);
}

/*
void server_listener(){
  // listen for incoming clients
  EthernetClient localClient = localServer.available();
  String msg;
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
          get_message(msg);
          speak(msg);
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
*/
