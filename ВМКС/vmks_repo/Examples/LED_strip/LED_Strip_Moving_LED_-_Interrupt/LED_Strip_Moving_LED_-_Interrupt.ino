#include <Adafruit_NeoPixel.h>
#define NUM_PIXELS 10
#define PIN 5
Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB);

#define BTN_LEFT 3
#define BTN_RIGHT 2

volatile uint8_t position = 0;

void L_button_pressed_ISR();
void R_button_pressed_ISR();

void setup() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_LEFT), L_button_pressed_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RIGHT), R_button_pressed_ISR, RISING);

  pinMode(PIN, OUTPUT);
  strip.begin();
}

void L_button_pressed_ISR() {
  if (position > 0) position--;
}

void R_button_pressed_ISR() {
  if (position < (NUM_PIXELS - 1)) position++;
}

void loop() {
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
