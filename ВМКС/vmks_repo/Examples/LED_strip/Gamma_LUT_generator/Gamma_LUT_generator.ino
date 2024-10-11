// Generate an LED gamma-correction table for Arduino sketches.
// Copy-and-paste the program's output into an Arduino sketch.

float gamma     = 2.2; // Correction factor
uint8_t max_in  = 255; // Top end of INPUT range
uint8_t max_out = 255; // Top end of OUTPUT range

uint8_t temp = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("const uint8_t PROGMEM gamma[] = {");
  for (int i = 0; i <= max_in; i++) {
    if (i > 0) Serial.print(',');
    if ((i & 15) == 0) Serial.print("\n  ");
    temp = (uint8_t)(pow((float)i / (float)max_in, gamma) * max_out + 0.5);
    Serial.print(temp);
  }
  Serial.println("\n };");
}

void loop() {

}
