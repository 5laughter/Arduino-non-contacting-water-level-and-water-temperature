//Library
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMPIXELS300 8 //Neopixel number
#define BRIGHTNESS 255

//PIN setup
int PIN = 13;
int buzzer = 12;
int levelSensor1 = 11;
int levelSensor2= 10;
int levelSensor3 = 9;

Adafruit_NeoPixel pixels300 = Adafruit_NeoPixel(NUMPIXELS300, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  //setup code
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  mlx.begin();
  pixels300.setBrightness(BRIGHTNESS);
  pixels300.begin();
  pixels300.show();
}

void loop() {
  int i = 0;
  int state100 = digitalRead(levelSensor1); //state of 100ml
  int state200 = digitalRead(levelSensor2); //state of 200ml
  int state300 = digitalRead(levelSensor3); //state of 300ml
  int temperature = mlx.readObjectTempC(); //temperature of object(water)
  
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");

  if (state100 == 0){
    if (state200 == 0){
      if (state300 == 0) {
        if (temperature > 40) { //if water level is 300ml and temperature>40
          Serial.println("hot 300ml");
          for (i = 0; i < 8; i++) {
            pixels.setPixelColor(i, pixels.Color(255, 0, 0)); //red
            pixels.show();
            delay(100);
          }
        }
        else if (25 < temperature){ //if water level is 300ml and 25<temperature<40
          Serial.println("warm 300ml");
          for (i =0; i < 8; i++) {
            pixels.setPixelColor(i, pixels.Color(255,60, 0,0)); //orange
            pixels.show();
            delay(100);
          }
        }
        else { //if water level is 300ml and temperature<25
          Serial.println("cool 300ml");
          for (i=0; i<8; i++) {
            pixels.setPixelColor(i, pixels.Color(0,0,255)); //blue
            pixels.show();
            delay(100);
          }
        }
        sound(1); //buzzer on
      }
      if (state300 == 1) {
        if (temperature > 40) { //if water level is 200ml and temperature>40
          Serial.println("hot 200ml");
          for (i = 0; i < 5; i++) {
            pixels.setPixelColor(8, pixels.Color(0,0,0,0));
            pixels.setPixelColor(7, pixels.Color(0,0,0,0));
            pixels.setPixelColor(6, pixels.Color(0,0,0,0));
            pixels.setPixelColor(5, pixels.Color(0,0,0,0));
            pixels.setPixelColor(i, pixels.Color(255, 0, 0)); //red
            pixels.show();
            delay(100);
          }
        }
        else if (25 < temperature){ //if water level is 200ml and 25<temperature<=40
          Serial.println("warm 200ml");
          for (i =0; i < 5; i++) {
            pixels.setPixelColor(8, pixels.Color(0,0,0,0));
            pixels.setPixelColor(7, pixels.Color(0,0,0,0));
            pixels.setPixelColor(6, pixels.Color(0,0,0,0));
            pixels.setPixelColor(5, pixels.Color(0,0,0,0));
            pixels.setPixelColor(i, pixels.Color(255,60,0,0)); //orange
            pixels.show();
            delay(100);
          }
        }
        else { //if water level is 200ml and temperature<25
          Serial.println("cool 200ml");
          for (i=0; i<5; i++) {
            pixels.setPixelColor(8, pixels.Color(0,0,0,0));
            pixels.setPixelColor(7, pixels.Color(0,0,0,0));
            pixels.setPixelColor(6, pixels.Color(0,0,0,0));
            pixels.setPixelColor(5, pixels.Color(0,0,0,0));
            pixels.setPixelColor(i, pixels.Color(0,0,255)); //blue
            pixels.show();
            delay(100);
          }
        }
      }
    }
    if(state200 == 1) {
      if(temperature > 40) { //if water level is 100ml and temperature>40
        Serial.println("hot 100ml");
        for(i=0; i<3; i++) {
          pixels.setPixelColor(8, pixels.Color(0,0,0,0));
          pixels.setPixelColor(7, pixels.Color(0,0,0,0));
          pixels.setPixelColor(6, pixels.Color(0,0,0,0));
          pixels.setPixelColor(5, pixels.Color(0,0,0,0));
          pixels.setPixelColor(4, pixels.Color(0,0,0,0));
          pixels.setPixelColor(3, pixels.Color(0,0,0,0));
          pixels.setPixelColor(i, pixels.Color(255, 0,0)); //red
          pixels.show();
          delay(100);
        }
      }
      else if(25 < temperature) { //if water level is 100ml and 25<temperature<=40
        Serial.println("warm 100ml");
        for(i=0; i<3; i++) {
          pixels.setPixelColor(8, pixels.Color(0,0,0,0));
          pixels.setPixelColor(7, pixels.Color(0,0,0,0));
          pixels.setPixelColor(6, pixels.Color(0,0,0,0));
          pixels.setPixelColor(5, pixels.Color(0,0,0,0));
          pixels.setPixelColor(4, pixels.Color(0,0,0,0));
          pixels.setPixelColor(3, pixels.Color(0,0,0,0));
          pixels.setPixelColor(i, pixels.Color(255,60,0,0)); //orange
          pixels.show();
          delay(100);
        }
      }
      else { //if water level is 100ml and temperature<25
        Serial.println("cool 100ml");
        for(i=0; i<3; i++){
          pixels.setPixelColor(8, pixels.Color(0,0,0,0));
          pixels.setPixelColor(7, pixels.Color(0,0,0,0));
          pixels.setPixelColor(6, pixels.Color(0,0,0,0));
          pixels.setPixelColor(5, pixels.Color(0,0,0,0));
          pixels.setPixelColor(4, pixels.Color(0,0,0,0));
          pixels.setPixelColor(3, pixels.Color(0,0,0,0));
          pixels.setPixelColor(i, pixels.Color(0,0,255,0)); //blue
          pixels.show();
          delay(100);
        }
      }
    }
  }
  if(state100 == 1) { //no water
    for(i=0; i<8; i++){
      pixels300.setPixelColor(i, pixels300.Color(0,0,0)); //off all neopixels
      pixels300.show();
      delay(100);
    }
    Serial.println("no water");
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

void sound(int t){ //buzzer function
  int i=0;
  for(i=0; i < t; i++){
    tone(buzzer, 300);
    delay(200);
    noTone(buzzer);
  }
}
