#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 42, 0, 17);

IPAddress nodeServer(192, 168, 0, 11);
// char nodeServer[] = "www.google.com";

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
EthernetClient client;

const int LM35 = A3; // Define o pino analógico que irá ler a saída do LM35
float temperature; // Variável que armazenará a temperatura medida

long lastReadingTime = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // check if already passed 5 seconds from the last read.
  if (millis() - lastReadingTime > 10000) {
    readTemperature();
    postTemperature(temperature);
    Serial.println();
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
    String request;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          if (request.indexOf("/temperature-manager/api/ac1?status=true") > 0){
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close"); // the connection will be closed after completion of the response        // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<h1>ac1 = true</h1>");
            client.println("</html>");
          } else if (request.indexOf("/temperature-manager/api/ac1?status=false") > 0) {
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close"); // the connection will be closed after completion of the response        // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<h1>ac1 = false</h1>");
            client.println("</html>");
          } else if (request.indexOf("/temperature-manager/api/ac2?status=true") > 0) {
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close"); // the connection will be closed after completion of the response        // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<h1>ac2 = true</h1>");
            client.println("</html>");
          } else if (request.indexOf("/temperature-manager/api/ac2?status=false") > 0) {
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close"); // the connection will be closed after completion of the response        // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<h1>ac2 = false</h1>");
            client.println("</html>");
          }

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
    delay(10);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void postTemperature(float temperature) {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();
  
  String temperatureStr = String(temperature);
  // if you get a connection, report back via serial:
  if (client.connect(nodeServer, 3000)) {
    Serial.println("connected");
    // Make a HTTP GET request:
    client.println("GET /temperature-manager/api/lm?temperature=" + temperatureStr + " HTTP/1.1");
    client.println("Host: 10.42.0.17"); // Add node server
    client.println("Connection: close");
    client.println();

    Serial.println("temperature posted");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void readTemperature() {
  temperature = ( float(analogRead(LM35)) * 5 / (1023) ) / 0.01;
  Serial.print("Temperatura: ");
  Serial.println(temperature);
}