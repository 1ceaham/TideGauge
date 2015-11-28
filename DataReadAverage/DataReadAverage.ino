#define alpha 0.8

void setup() {
  Serial.begin(9600);
}

void loop() {
  static int counter = 0;
  int nSamps = 25;
  int value[nSamps];
  value[counter%nSamps] = analogRead(0);
  
  if(counter%nSamps==0){  
    double average = 0;
    for(int i=0; i<nSamps; i++){
      average = average + value[i];
    }
    average = average / (double)nSamps;
    
    Serial.println(String(average) + " " + String(counter));
  }
  
  //Serial.println(String(value[counter%nSamps]));
  counter++;
  delay(50);
}
