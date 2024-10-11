#include <Adafruit_NeoPixel.h>
#define LED_PIN 6
#define LED_ROW 8
#define LED_COL 8
#define LED_COUNT (LED_ROW * LED_COL)

Adafruit_NeoPixel matrix(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t brightness = 0;

void setup() {
  matrix.begin();
  matrix.show();
  matrix.setBrightness(255);
}

void loop() {
  for (uint32_t x = 0; x < 100; x++) {
    //brightness = (x*250)/100;   // Gamma - NO
    //brightness = (x*x)/40;      // Gamma - 2
    brightness = (x*x*x)/4000;    // Gamma - 3
    matrix.setPixelColor(0, (uint8_t)brightness, 0, 0);
    matrix.show();
    delay(20); 
  }
  for (uint32_t x = 100; x > 0; x--) {
    //brightness = (x*250)/100;   // Gamma - NO
    //brightness = (x*x)/40;      // Gamma - 2
    brightness = (x*x*x)/4000;    // Gamma - 3
    matrix.setPixelColor(0, (uint8_t)brightness, 0, 0);
    matrix.show();
    delay(20); 
  }
}
