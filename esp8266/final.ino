char servername[] = "camaleao.museu-goeldi.br";

float voltageRead;
float temperature;


void setup() {
    Serial.begin(115200);
}

void loop() {

}

void sendDataToServer() {
    if (client.connect(servername, 80)) {  //starts client connection, checks for connection
        Serial.println("connected");
        client.println("GET /send_email.php?temperature="+temperature+" HTTP/1.1"); //Send data
        client.println("Host: "+servername);
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
    temperature = voltageRead/3.26;
    delay(1000);
}