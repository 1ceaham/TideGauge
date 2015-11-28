#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Suli.h>

#define PIN_TX    7
#define PIN_RX    8
//make sure that the baud rate of SIM900 is 9600!
//you can use the AT Command(AT+IPR=9600) to set it through SerialDebug
#define BAUDRATE  9600


GPRS gprs(PIN_TX, PIN_RX, BAUDRATE, "epc.t-mobile", NULL, NULL);

void publishData(String data) {

  Serial.println("attempting to publish");

  while (false == gprs.join()) {
    Serial.println("gprs join network error");
    delay(2000);
  }

  String str = "GET /publish/pub-c-ed878dba-b69d-4a36-81af-568acae8a20f/sub-c-280d5980-88a9-11e5-9320-02ee2ddab7fe/0/pubnub_gprs/0/\"" + data + "\" HTTP/1.0\r\n\r\n";
  // was String str = "GET /publish/demo/demo/0/pubnub_gprs/0/\"" + data + "\" HTTP/1.0\r\n\r\n";
  
  // Length (with one extra character for the null terminator)
  int str_len = str.length() + 1; 

  // Prepare the character array (the buffer) 
  char http_cmd[str_len];

  // Copy it over 
  str.toCharArray(http_cmd, str_len);

  // char buffer[512];

  if (false == gprs.connect(TCP, "pubsub.pubnub.com", 80)) {
    Serial.println("connect error");
  } else {
    Serial.println("publish success");
    Serial.println(data);
  }

  gprs.send(http_cmd, sizeof(http_cmd) - 1);

  gprs.close();

}

void setup() {

  Serial.println("starting");

  Serial.begin(9600);
  // use DHCP
  gprs.init();
  // attempt DHCP
  
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
    publishData(String(average));
  }
  
  //Serial.println(String(value[counter%nSamps]));
  counter++;
  delay(50);

}
