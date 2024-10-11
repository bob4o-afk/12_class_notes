#define LED 9
uint32_t br = 0;
void setup() {
  pinMode(LED, OUTPUT);
}
void loop() {
  for (uint32_t x = 0; x < 100; x++) {
    //br = (x*250)/100;   // Gamma - NO
    //br = (x*x)/40;      // Gamma - 2
    br = (x*x*x)/4000;    // Gamma - 3
    analogWrite(LED,br);
    delay(20);
  }
  for (uint32_t x = 100; x > 0; x--) {
    //br = (x*250)/100;   // Gamma - NO
    //br = (x*x)/40;      // Gamma - 2
    br = (x*x*x)/4000;    // Gamma - 3
    analogWrite(LED,br);
    delay(20);
  }
}
