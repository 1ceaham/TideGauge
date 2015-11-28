#define alpha 0.8

void setup() {
  Serial.begin(9600);
}

void loop() {
  static int counter = 0;
  int nSamps = 25;
  int newValue = analogRead(0);
  static double oldValue = 0;
  double smoothValue[nSamps];
  smoothValue[counter%nSamps] = alpha * oldValue + (1 - alpha) * newValue;
  oldValue = newValue;
  
  if(counter%nSamps==0){  
    double average = 0;
    for(int i=0; i<nSamps; i++){
      average = average + smoothValue[i];
    }
    average = average / (double)nSamps;
    //oldValue = average;
    
    Serial.println(String(average) + " " + String(oldValue) + " " + String(counter));
  }
  
  //Serial.println(String(smoothValue[counter%nSamps]));
  counter++;
  delay(50);
}
