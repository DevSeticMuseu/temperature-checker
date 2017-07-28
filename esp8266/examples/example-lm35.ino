float inp;
float cent;

void setup(){
  Serial.begin(115200);
}

void loop(){
  inp = analogRead(A0);
  cent = inp/3.26;
  Serial.println(cent);
  delay(1000);
}
