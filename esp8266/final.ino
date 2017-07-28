#include <ESP8266WiFi.h>

const char* ssid     = "OCapitalismo";
const char* password = "asds";
const char servername[] = "192.168.0.11"; // remote server we will connect to

float voltageRead;
float temperature;

String temperatureString;

WiFiClient client;

void setup() {
    Serial.begin(115200);
    Serial.println("Connecting");
    
    WiFi.begin(ssid, password);
    // attempt to connect to Wifi network:
    while ( WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to connect to network, SSID: ");
        Serial.println(ssid);

        // wait 10 seconds for connection:
        delay(3000);
    }

    Serial.println("Connected");
}

void loop() {
    delay(3000);
    readSensor();
    if( temperature >= 20 ){
        temperatureString = String(temperature);
        sendDataToServer(temperatureString);
    }
}

void sendDataToServer(String temp) {
    String result;
    if (client.connect(servername, 80)) {  //starts client connection, checks for connection
        Serial.println("connected");
        client.println("GET /send-email/email.php?temperature="+temp+" HTTP/1.1"); //Send data
        client.println("Host: 192.168.0.11");
        client.println("Connection: close");  //close 1.1 persistent connection  
        client.println(); //end of get request
    } else {
        Serial.println("connection failed"); //error message if no client connect
        Serial.println();
    }

    while(client.connected() && !client.available()) delay(1); //waits for data
    while (client.connected() || client.available()) { //connected or data available
        char c = client.read(); //gets byte from ethernet buffer
        result = result+c;
    }

    client.stop(); //stop client
    Serial.println(result);
}

void readSensor() {
    voltageRead = analogRead(A0);
    temperature = voltageRead/3.33;
}
