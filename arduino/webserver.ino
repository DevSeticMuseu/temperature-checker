#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 17);

IPAddress nodeServer(74,125,232,128);
// char nodeServer[] = "www.google.com"; 

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
EthernetClient client;

long lastReadingTime = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // check if already passed 5 seconds from the last read.
  if (millis() - lastReadingTime > 5000) {
    postTemperature();
    lastReadingTime = millis();
  }

  listenForEthernetClients();
}

void listenForEthernetClients(){
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
         // send a standard http response header
         client.println("HTTP/1.1 200 OK");
         client.println("Content-Type: text/html");
          // Control air conditioner
          Serial.println("Execute command");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(100);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void postTemperature(int temperature){
  // if you get a connection, report back via serial:
  if (client.connect(nodeServer, 80)) {
    Serial.println("connected");
    // Make a HTTP POST request:
    client.println("POST /sensor/api/"+ temperature +" HTTP/1.1");
    client.println("Host: www.server.com");
    client.println("Connection: close");
    client.println();

    Serial.println("temperature posted");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}