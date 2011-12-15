long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
int port = 3000;

EthernetClient client;
IPAddress server(192,168,0,189); // Local

void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.println("connecting to server...");
  if (client.connect(server, port)) {
    Serial.println("making HTTP request...");
    client.println("GET /chatter_feed/feed HTTP/1.1");
    client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}   

