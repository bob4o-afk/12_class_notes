#define RS  12
#define EN  11
#define D4  5
#define D5  4
#define D6  3
#define D7  2

#define COLS 16
#define ROWS 2

void setup() {
  // Initialize LCD screen and IF GPIO
  lcd_init();

  // Show hardcoded text "VMKS"
  lcd_show_text_vmks();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void lcd_init() {
  // Set IF GPIO mode
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  // LCD Power-On Reset (POR) initialization wait
  delay(40);

  // Initialize controller HD44780
    lcd_cmd(B0010, 0); delayMicroseconds(5*39); // Function set => 4-bit data bus mode, 1-line, 5x8 dots
  lcd_cmd(B0010, 0); lcd_cmd(B1000, 0); delayMicroseconds(5*39);   // Function set => 4-bit data bus mode, 2-line, 5x8 dots
  lcd_cmd(B0000, 0); lcd_cmd(B0110, 0); delayMicroseconds(5*39);   // entry mode set = left-justified, left-to-right, no shift text
  lcd_cmd(B0000, 0); lcd_cmd(B0001, 0); delayMicroseconds(5*1530); // clear display - set all characters to space(' ') and return cursor to begining of first row (return home)
  lcd_cmd(B0000, 0); lcd_cmd(B1100, 0); delayMicroseconds(5*39);   // turn display on
}

// Send ASCII text "VMKS"
void lcd_show_text_vmks() {
  lcd_cmd(B0101, 1); lcd_cmd(B0110, 1); delayMicroseconds(5*43); // write data to DDRAM // V = 0x56 = B 0101 0110
  lcd_cmd(B0100, 1); lcd_cmd(B1101, 1); delayMicroseconds(5*43); // write data to DDRAM // M = 0x4D = B 0100 1101
  lcd_cmd(B0100, 1); lcd_cmd(B1011, 1); delayMicroseconds(5*43); // write data to DDRAM // K = 0x4B = B 0100 1011
  lcd_cmd(B0101, 1); lcd_cmd(B0011, 1); delayMicroseconds(5*43); // write data to DDRAM // S = 0x53 = B 0101 0011
}

// Data = 4-bit data to send (use lower 4 bits)
// Type 0 = Instruction || Type 1 = Data
// Delay values are show just as example and are
// minimum requiered values in [ns] multiplied by 2
void lcd_cmd(uint8_t _data, bool _type) {
  // Set RS
  digitalWrite(RS, _type);

  // Set Data value
  digitalWrite(D4, (_data & 0x01));
  digitalWrite(D5, (_data & 0x02));
  digitalWrite(D6, (_data & 0x04));
  digitalWrite(D7, (_data & 0x08));

  // Time to select the register
  delayMicroseconds(2*100); // tsu
  // Data setup time = 60~90ns after the above delay
  // In this example data is already set before that

  // Pulse Enable
  digitalWrite(EN, HIGH);
  delayMicroseconds(2*300); // tw - Enable pulse duration
  digitalWrite(EN, LOW);

  // Wait
  delayMicroseconds(2*10); // tc/th1/th2 - Data hold time
}
