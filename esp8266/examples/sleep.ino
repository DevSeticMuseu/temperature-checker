/**
 * An example showing how to put ESP8266 into Deep-sleep mode
 */
 
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while(!Serial) { }

  pinMode(D1, OUTPUT); 

  delay(3000);
}

void loop() {

  delay(2000);

  Serial.println("I'm awake.");

  digitalWrite(D1, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(5000);   

  digitalWrite(D1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  

  Serial.println("Going into deep sleep for 20 seconds");
  ESP.deepSleep(20e6); // 20e6 is 20 microseconds
}
