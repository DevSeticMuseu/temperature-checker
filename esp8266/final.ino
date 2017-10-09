#include <ESP8266WiFi.h>

extern "C" {

#include "user_interface.h"
}

WiFiClient client;

const char* ssid     = "MPEG-STI";
const char* senha = "w1f1mpeg";
const char servidor[] = "camaleao.museu-goeldi.br";
const char port = 80;

String stringTemperatura;

float voltagemMedida;
float temperaturaMedida;

int contadorAltaTemp = 0;
int contadorBaixaTemp = 0;
int mediaTemperatura = 23;
int temperaturaDeAlerta = 23;

void setup() {
    //Inicia pino do led como saída
    pinMode(D1, OUTPUT);
    WiFi.begin(ssid, senha);

    testaConexao();

    WiFi.mode(WIFI_STA);
    wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void loop() {    
    testaConexao();
    lerSensor();
    trataTemperatura(temperaturaMedida);
    //Espera 60 segundos
    delay(60000);
}

//Conecta ao servidor e chama o script php para enviar email
void enviaEmail(String nivel, String temp) {
    String result;
    if (client.connect(servidor, port)) {  //starts client connection, checks for connection
        Serial.println("conectado");
        client.println("GET /send-email/email-"+nivel+".php?temperatura="+temp+" HTTP/1.1"); //Send data
        client.println("Host: camaleao.museu-goeldi.br");
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

void lerSensor() {
    voltagemMedida = analogRead(A0);
    temperaturaMedida = ((voltagemMedida*3.03)/1024)/0.01;
}

/* Testa conexão. Caso não consiga conectar ao wifi,
   acende o led e espera o estabelecimento de conexão */
void testaConexao() {
    if ( WiFi.status() != WL_CONNECTED ){
        digitalWrite(D1, HIGH);
        
        while ( WiFi.status() != WL_CONNECTED) {
            //Espera 5 segundos antes de tentar outra vez
            delay(5000);
        }
    }
    digitalWrite(D1, LOW);
}

void trataTemperatura(float tempMedida) {
    //Envia um email a cada aumento de um grau na temperatura.
    if( tempMedida >= mediaTemperatura ){
        contadorAltaTemp += 1;
        if ( contadorAltaTemp >= 3 ){
            stringTemperatura = String(temperaturaMedida);
            enviaEmail("aumentou", stringTemperatura);
            mediaTemperatura += 1;
            contadorAltaTemp = 0;
        }
    } else{
        contadorAltaTemp = 0;
    }

    /* Caso a temperatura meça menos dois graus em relação a última temperatura de alerta,
    envia um email informando que a temperatura está se estabilizando. */
    if( tempMedida <= (mediaTemperatura-2) && mediaTemperatura > temperaturaDeAlerta ){
        contadorBaixaTemp += 1;
        if ( contadorBaixaTemp >= 3 ){
            mediaTemperatura -= 1;
            stringTemperatura = String(mediaTemperatura);
            enviaEmail("diminuiu", stringTemperatura);
            contadorBaixaTemp = 0;
        }
    } else{
        contadorBaixaTemp = 0;
    }
}
