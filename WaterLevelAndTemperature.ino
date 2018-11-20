/*
  이 코드는 네오픽셀 8개 기준으로 작성된 코드임.
  비접촉 수위 센서에 감지 됨에 따라 불이 켜지는 스트립형 네오픽셀의 개수가 달라지고,
  수온에 따라 파랑색, 주황색, 빨간색 등으로 네오 픽셀의 색이 바뀜.
*/
//라이브러리
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_NeoPixel.h>
//네오픽셀 사용 특수 코드
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMPIXELS300 8 // 네오 픽셀 개수
#define BRIGHTNESS 255 // 네오픽셀 밝기 설정 0(어두움) ~ 255(밝음)

int PIN = 13; //네오 픽셀 PIN번호
int buzzer = 12; //버저 PIN번호
int levelSensor1 = 11; //100ml 수위 센서 PIN
int levelSensor2= 10; //200ml 수위 센서 PIN
int levelSensor3 = 9; //300ml 수위 센서 PIN

Adafruit_NeoPixel pixels300 = Adafruit_NeoPixel(NUMPIXELS300, PIN, NEO_GRBW + NEO_KHZ800); //네오픽셀 선언
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, PIN, NEO_GRBW + NEO_KHZ800); //네오픽셀 선언
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //온도센서 사용 선언

void setup() {
  //아래는 설정 코드
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  mlx.begin();
  pixels300.setBrightness(BRIGHTNESS);
  pixels300.begin();
  pixels300.show();
}

void loop() {
  int i = 0;
  int state100 = digitalRead(levelSensor1); //100ml의 상태
  int state200 = digitalRead(levelSensor2); //200ml의 상태
  int state300 = digitalRead(levelSensor3); //300ml의 상태
  int temperature = mlx.readObjectTempC(); //Object 온도 값
  
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C"); //온도 값 출력

  if (state100 == 0){
    if (state200 == 0){
      if (state300 == 0) {
        if (temperature > 40) { // 300ml 이고 40도 이상이면
          Serial.println("hot 300ml"); //출력
          for (i = 0; i < 8; i++) {
            pixels.setPixelColor(i, pixels.Color(255, 0, 0)); //빨간색
            pixels.show();
            delay(100);
          }
        }
        else if (25 < temperature){ // 300ml 이고 25~40도이면
          Serial.println("warm 300ml"); //출력
          for (i =0; i < 8; i++) {
            pixels.setPixelColor(i, pixels.Color(255,60, 0,0)); //주황
            pixels.show();
            delay(100);
          }
        }
        else { //25도 미만
          Serial.println("cool 300ml"); //출력
          for (i=0; i<8; i++) {
            pixels.setPixelColor(i, pixels.Color(0,0,255)); //파랑
            pixels.show();
            delay(100);
          }
        }
        sound(1); //300ml 일 때 소리를 낸다
      }
      if (state300 == 1) {
        if (temperature > 40) { //200ml이고 40도 이상일 때
          Serial.println("hot 200ml"); //출력
          for (i = 0; i < 5; i++) {
            pixels.setPixelColor(8, pixels.Color(0,0,0,0));
            pixels.setPixelColor(7, pixels.Color(0,0,0,0));
            pixels.setPixelColor(6, pixels.Color(0,0,0,0));
            pixels.setPixelColor(5, pixels.Color(0,0,0,0));
            pixels.setPixelColor(i, pixels.Color(255, 0, 0)); //빨간색
            pixels.show();
            delay(100);
          }
        }
        else if (25 < temperature){ //25~40도이면
          Serial.println("warm 200ml"); //출력
          for (i =0; i < 5; i++) {
            pixels.setPixelColor(8, pixels.Color(0,0,0,0));
            pixels.setPixelColor(7, pixels.Color(0,0,0,0));
            pixels.setPixelColor(6, pixels.Color(0,0,0,0));
            pixels.setPixelColor(5, pixels.Color(0,0,0,0));
            pixels.setPixelColor(i, pixels.Color(255,60,0,0)); //주황
            pixels.show();
            delay(100);
          }
        }
        else { //25도 미만
          Serial.println("cool 200ml"); //출력
          for (i=0; i<5; i++) {
            pixels.setPixelColor(8, pixels.Color(0,0,0,0));
            pixels.setPixelColor(7, pixels.Color(0,0,0,0));
            pixels.setPixelColor(6, pixels.Color(0,0,0,0));
            pixels.setPixelColor(5, pixels.Color(0,0,0,0));
            pixels.setPixelColor(i, pixels.Color(0,0,255)); //파랑
            pixels.show();
            delay(100);
          }
        }
      }
    }
    if(state200 == 1) {
      if(temperature > 40) { //100ml 40도 이상이면
        Serial.println("hot 100ml"); //출력
        for(i=0; i<3; i++) {
          pixels.setPixelColor(8, pixels.Color(0,0,0,0));
          pixels.setPixelColor(7, pixels.Color(0,0,0,0));
          pixels.setPixelColor(6, pixels.Color(0,0,0,0));
          pixels.setPixelColor(5, pixels.Color(0,0,0,0));
          pixels.setPixelColor(4, pixels.Color(0,0,0,0));
          pixels.setPixelColor(3, pixels.Color(0,0,0,0));
          pixels.setPixelColor(i, pixels.Color(255, 0,0)); //빨간색
          pixels.show();
          delay(100);
        }
      }
      else if(25 < temperature) { //100ml 25~40도
        Serial.println("warm 100ml"); //출력
        for(i=0; i<3; i++) {
          pixels.setPixelColor(8, pixels.Color(0,0,0,0));
          pixels.setPixelColor(7, pixels.Color(0,0,0,0));
          pixels.setPixelColor(6, pixels.Color(0,0,0,0));
          pixels.setPixelColor(5, pixels.Color(0,0,0,0));
          pixels.setPixelColor(4, pixels.Color(0,0,0,0));
          pixels.setPixelColor(3, pixels.Color(0,0,0,0));
          pixels.setPixelColor(i, pixels.Color(255,60,0,0)); //주황
          pixels.show();
          delay(100);
        }
      }
      else { //25도 미만
        Serial.println("cool 100ml"); //출력
        for(i=0; i<3; i++){
          pixels.setPixelColor(8, pixels.Color(0,0,0,0));
          pixels.setPixelColor(7, pixels.Color(0,0,0,0));
          pixels.setPixelColor(6, pixels.Color(0,0,0,0));
          pixels.setPixelColor(5, pixels.Color(0,0,0,0));
          pixels.setPixelColor(4, pixels.Color(0,0,0,0));
          pixels.setPixelColor(3, pixels.Color(0,0,0,0));
          pixels.setPixelColor(i, pixels.Color(0,0,255,0)); //파랑
          pixels.show();
          delay(100);
        }
      }
    }
  }
  if(state100 == 1) { //물이 없으면
    for(i=0; i<8; i++){
      pixels300.setPixelColor(i, pixels300.Color(0,0,0)); //다 끔
      pixels300.show();
      delay(100);
    }
    Serial.println("no water"); //출력
  }
  Serial.println();
  delay(100);
}

void colorWipe300(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels300.numPixels(); i++) {
    pixels300.setPixelColor(i, c);
    pixels300.show();
    delay(wait);
  }
}

void sound(int t){ //버저를 울리는 함수
  int i=0;
  for(i=0; i < t; i++){
    tone(buzzer, 300);
    delay(200);
    noTone(buzzer);
  }
}
