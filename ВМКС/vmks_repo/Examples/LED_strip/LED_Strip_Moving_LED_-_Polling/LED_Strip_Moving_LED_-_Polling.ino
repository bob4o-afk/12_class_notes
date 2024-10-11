#include <Adafruit_NeoPixel.h>
#define NUM_PIXELS 10
#define PIN 5
Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB);

#define BTN_LEFT 3
#define BTN_RIGHT 2

uint8_t position = 0;

void setup() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  pinMode(PIN, OUTPUT);
  strip.begin();
}

void loop() {
  if (digitalRead(BTN_LEFT) == LOW)
  {
    if (position > 0) position--;
  }
  if (digitalRead(BTN_RIGHT) == LOW)
  {
    if (position < (NUM_PIXELS - 1)) position++;
  }
  delay(50);

  for (int i = 0 ; i < NUM_PIXELS; i++)
  {
    if (i == position)
    {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
  }
  strip.show();
}
