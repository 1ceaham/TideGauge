void setup() {
  Serial.begin(9600);
}

void loop() {
  int data = analogRead(0);
  Serial.println(String(data+500));
  delay(50);
}
