#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin();

  DDRD &= ~((1 << DDD4) | (1 << DDD5) | (1 << DDD6));

  PORTD |= (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6);
}

void loop() {
  pixels.clear();

  int pinID = 0;
  pinID |= (PIND & (0b111 << PIND4)) >> 4;

  Serial.println(pinID);
  pixels.setBrightness(20);

  pixels.setPixelColor(pinID, pixels.Color(0, 150, 0)); 
  pixels.show();
}
