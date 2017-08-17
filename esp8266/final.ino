#include <ESP8266WiFi.h>

extern "C" {

#include "user_interface.h"
}

const char* ssid     = "O capitalismo";
const char* password = "04091972B,jnts";
const char servername[] = "10.0."; // remote server we will connect to

float voltageRead;
float temperature;

int highTempCont = 0;

String temperatureString;

WiFiClient client;

void setup() {
    Serial.begin(115200);
    Serial.println("Connecting");

    //Inicia pino do led como saída
    pinMode(D1, OUTPUT);

    WiFi.begin(ssid, password);

    testConnection();
    
    Serial.println("Connected");

    WiFi.mode(WIFI_STA);
    wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void loop() {    
  
    testConnection();

    readSensor();

    Serial.print( "The temperature is: " );
    Serial.println( temperature );

//    if( temperature >= 20 ){
//        highTempCont += 1;
//        Serial.print( highTempCont );
//        if ( highTempCont >= 10 ){
//            Serial.println( "Enviando informações por email" );
//            temperatureString = String(temperature);
//            sendDataToServer(temperatureString);
//            highTempCont = 0;
//        }
//    }
//    else{
//        highTempCont = 0;
//    }

    Serial.println("Indo dormir por 30 secs");

    //Espera 10 segundos
    delay(10000);
}

void sendDataToServer(String temp) {
    String result;
    if (client.connect(servername, 80)) {  //starts client connection, checks for connection
        Serial.println("connected");
        client.println("GET /send-email/email.php?temperature="+temp+" HTTP/1.1"); //Send data
        client.println("Host: 10.0.0");
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
    temperature = voltageRead/3.3;
}

/* Testa conexão. Caso não consiga conectar ao wifi,
   acende o led e espera o estabelecimento de conexão */
void testConnection(){
    Serial.println("Testando conexão");

    if ( WiFi.status() != WL_CONNECTED){
        digitalWrite(D1, HIGH);
        
        while ( WiFi.status() != WL_CONNECTED) {
            Serial.print("Attempting to connect to network, SSID: ");
            Serial.println(ssid);

            //Espera 5 segundos antes de tentar outra vez
            delay(5000);
        }
    }

    digitalWrite(D1, LOW);
}