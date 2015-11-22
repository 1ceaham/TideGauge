/////////////////////////////////////////////////////////////////
// a2dToSerialMaxMultiple
// Michael Gurevich
// Oct 1, 2013
//
// Demonstrates sending an multiple sensor values as serial data
// to Max
/////////////////////////////////////////////////////////////////

 
void setup() {
  Serial.begin(9600);    // setup serial, **NOTE BAUD RATE**
}

void loop() {
  a2dStep();
  delay(10);
}

void a2dStep() {  
  int val[2];
  Serial.write(255);	//send separator byte

  for (int i=0; i<2; i++) {
	val[i] = analogRead(i);  // read the value of analog pin i
    Serial.write(val[i]>>3);    // send 7 MSB as serial data
    Serial.write(val[i]&7);	 // send 3 LSB as serial data
  }

}






