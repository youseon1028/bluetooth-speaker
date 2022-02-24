#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define PIN 10
#define NUMS 11
#define TX 2 
#define RX 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMS, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial blueTooth(TX, RX);
byte colors[5]; // 색상을 받아오는 배열


void setup() {
  blueTooth.begin(9600); // 블루투스 통신 준비, 통신속도는 9600 보드레이트로 설정
  Serial.begin(9600); // 시리얼 모니터 준비
  strip.begin(); // LED 제어 준비
  delay(1000); // 1초 기다렸다가 켜지게 하기
  rainbow(20); // rainbow 효과가 나오면서 켜지도록 하기
  strip.show(); // LED 전원이 꺼진 상태로 초기화하기
}

void loop() { 
  if(blueTooth.available() > 0) { // 데이터가 들어온 게 있다면
    blueTooth.readBytes(colors, 5); // colors 배열에 해당 데이터를 입력한다.
    if(colors[4] == (byte) 0) { // 일반적인 경우라면
      for(byte i = 0; i<4; i++) { // 각각의 데이터를
        Serial.println(colors[i]); // 시리얼 모니터에 출력한다.
      }
      for(byte i = 0;i<NUMS; i++) { // 각각의 픽셀에 
        strip.setPixelColor(i, colors[0], colors[1], colors[2]); // RGB 색상을 지정한다.
      }
      strip.setBrightness(colors[3]); // 밝기를 설정한다.
      // setPixelColor 함수가 스트립 객체에 보낼 메모리 이미지를 형성하고,
      // show 함수가 해당 이미지를 스트립 객체로 보낸다.
      strip.show(); // 밝기, 색상 정보를 스트립 객체로 보내고 LED를 켠다.
      delay(20); // 20 밀리세컨드 기다린다.
    }
    else if(colors[4] == (byte) 1) { // 레인보우 기능을 켠다면
      rainbow(20); // 레인보우 함수를 호출한다.
      delay(20); // 20 밀리세컨드 기다린다.
    }
  }
}

// 표현할 수 있는 색을 순서대로 표현하는 함수
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// 색을 지정해주는 함수
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
