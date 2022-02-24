#include <SoftwareSerial.h>

int Tx = 2; //전송 보내는핀  
int Rx = 3; //수신 받는핀

SoftwareSerial BtSerial(Tx,Rx);

void setup() {
  Serial.begin(9600);
  BtSerial.begin(9600);
  Serial.println("시작");
  
}

void loop() {
  if (BtSerial.available()) {       
    Serial.write(BtSerial.read());
  }
  if (Serial.available()) {         
    BtSerial.write(Serial.read());
  }
}
