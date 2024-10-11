#define LATCH_PIN 4
#define CLK_PIN   7
#define SDI_PIN   8

int print_digit(uint8_t segment, uint8_t value);

// Segment map to select number 0 to F
const uint8_t SEGMENT_MAP[16] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
// Byte map to select digit 0 to 3
const uint8_t SEGMENT_SELECT[4] = {0xF1, 0xF2, 0xF4, 0xF8};

void setup()
{
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(SDI_PIN, OUTPUT);
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(SDI_PIN, LOW);
}

void loop()
{
  print_digit(0, 5);
  print_digit(1, 6);
  print_digit(2, 7);
  print_digit(3, 9);
}

// Write a decimal number between 0 and 9 to one of the 4 digits of the display
int print_digit(uint8_t segment, uint8_t value)
{
  if (value > 15 || segment > 3)
  {
    return -1;
  }
  
  shiftOut(SDI_PIN, CLK_PIN, MSBFIRST, SEGMENT_MAP[value]);
  shiftOut(SDI_PIN, CLK_PIN, MSBFIRST, SEGMENT_SELECT[segment] );
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);

  return 0;
}
