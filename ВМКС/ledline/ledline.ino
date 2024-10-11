#include <Adafruit_NeoPixel.h>
#define PIN        4
#define NUMPIXELS  8

int currentPixels = 0;
int potentiometerPin = A1;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL   20  // Delay between colors, adjust for speed of the rainbow

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();

  pinMode(potentiometerPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  rainbowCycle(DELAYVAL);  // Call the function to display the rainbow
}

// Function to create the rainbow cycle effect
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on the wheel
    int value = analogRead(potentiometerPin);
    Serial.println(value);

    currentPixels = map(value, 0, 1010, 0, 8);
    for(i=0; i < currentPixels; i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / currentPixels) + j) & 255));
    }

    for(int p=currentPixels; p < NUMPIXELS; p++) {
      pixels.setPixelColor(p, 0, 0, 0);
    } 

    pixels.setBrightness(80);
    pixels.show();
    delay(wait);
  }
}

// Function to generate rainbow colors across 0-255 positions
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}