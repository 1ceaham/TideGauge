#define alpha 0.8

void setup() {
  Serial.begin(9600);
}

void loop() {
  static int counter = 0;
  static double lastValue = 0;
  int newValue = analogRead(0);
  double smoothValue[10];
  smoothValue[counter%10] = alpha * lastValue + (1 - alpha) * newValue;
  lastValue = newValue;
  if(counter%10==0){
    double average = 0;
    for(int i=0; i<10; i++){
      average = average + smoothValue[i];
    }
    average = average / 10;
    Serial.println("#S|LEAKTEST|["+String(average)+"]#");
  }
  Serial.println(String(smoothValue[counter%10]));
  counter++;
  delay(50);
}
