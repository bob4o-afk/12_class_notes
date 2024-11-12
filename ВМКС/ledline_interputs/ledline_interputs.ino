#include <Adafruit_NeoPixel.h>

#define PIN        10
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB);

void button_pressed_up ();
void button_pressed_down ();
volatile int8_t ledNumber = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), button_pressed_down, FALLING);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), button_pressed_up, FALLING);

  pixels.begin();
}

void loop() {
  pixels.clear();
  pixels.setBrightness(40);
  pixels.setPixelColor(ledNumber, pixels.Color(0, 150, 0));
  pixels.show();
  delay(10);

}

void button_pressed_up (){
  ledNumber += 1;
  if(ledNumber > 7){
    ledNumber = 0;
  }
}

void button_pressed_down (){
  ledNumber -= 1;
  if(ledNumber < 0){
    ledNumber = 7;
  }
}