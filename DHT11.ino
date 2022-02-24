#include <DHT.h> //온습도 센서 라이브러리 사용
#define DHTPIN 2 // 습도센서 Signal 선 연결
#define DHTTYPE DHT11
#include <SoftwareSerial.h> // 시리얼 통신
#include <Servo.h>
Servo myservo;

int relay=10; // 릴레이 단자
int Smoter=5;
int pos=0;
int Tx = 6; // 전송 핀
int Rx = 7; // 수신 핀

float hum;
float temp;
SoftwareSerial btSerial(Tx, Rx); // 설정한 핀으로 시리얼 통신 시작
DHT dht(DHTPIN, DHTTYPE);
void setup() 
{
  Serial.begin(9600);
  btSerial.begin(9600); // 보드레이트 9600으로 통신
  dht.begin();
  myservo.attach(5);
}
void loop() 
{
  int hum = dht.readHumidity();//온도값 읽기
  int temp= dht.readTemperature();//습도값 읽기
  char data[7] = {0,};
  Serial.println(hum); 

  if(hum<=40){   // 습도 100에서 시작해서 40이 되면 건조해진 것이기 때문에 서보모터 on(가습기 on)
    while(pos<180){ pos++; myservo.write(pos); delay(10); }
  }
  else if(hum>=60){    // 습도 0에서 시작해서 60이 되면 습해진 것이기 때문에 서보모터 on(가습기 off)
    while(pos>0){ pos--; myservo.write(pos); delay(10); }
  }
  //
  delay(1000);
  
  btSerial.print(hum);
  btSerial.print(",");
  btSerial.print(temp);
  
  btSerial.println();
  delay(1);
}
