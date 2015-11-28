void setup() {
  Serial.begin(9600);
}

void loop() {
  int data = analogRead(0);
  Serial.println("#S|BAYLANDS|["+String(data)+"]#");
  delay(50);
}
