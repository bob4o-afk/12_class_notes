#include <Adafruit_NeoPixel.h>

#define PIN 10
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB);
#define DELAYVAL 500

int currLed = 0;
int hasBeenPressedLeft = 0;
int hasBeenPressedRight = 0;

void setup() {
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pixels.begin();
}

void loop() {
  int isRight = digitalRead(9);
  int isLeft = digitalRead(8);

  if(isRight && hasBeenPressedRight == 0){
    hasBeenPressedRight = 1;
    currLed++;
  }else if(isRight == 0 && hasBeenPressedRight == 1){
    hasBeenPressedRight = 0;
  }

  if(isLeft && hasBeenPressedLeft == 0){
    hasBeenPressedLeft = 1;
    currLed--;
  }else if(isLeft == 0 && hasBeenPressedLeft == 1){
    hasBeenPressedLeft = 0;
  }

  pixels.clear();
  pixels.setBrightness(30);

  if(currLed < 0){
    currLed = 7;
  }else if(currLed > 7){
    currLed = 0;
  }

  pixels.setPixelColor(currLed, pixels.Color(150, 0, 0));
  pixels.show();
  delay(DELAYVAL);
}
