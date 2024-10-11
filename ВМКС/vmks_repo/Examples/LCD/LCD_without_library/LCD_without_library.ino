#define RS  12
#define EN  11
#define D4  5
#define D5  4
#define D6  3
#define D7  2

#define COLS 16
#define ROWS 2

void lcd_cmd(uint8_t _data, bool _type);
void lcd_init(void);
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_show_char(char chr);
void lcd_show_text(char *text, uint8_t len);
void lcd_show_text_vmks(void);

void setup() {
  // Initialize LCD screen and IF GPIO
  lcd_init();

  // Center the text on the second line => Move cursor to
  // (second line offset + half the line size - half the text size)
  // (0x40 + 16/2 - 4/2) = (0x40 + 8 - 2) = (0x40 + 6) = 0x46
  // Line 1 => 0x00 to 0x27
  // Line 2 => 0x40 to 0x67
  //lcd_cmd(B1100, 0); lcd_cmd(B0110, 0); // manually set DDRAM to cursor position = 0x46 = B 0100 0110
  lcd_set_cursor(6, 2); // the same but using the function

  // Show text
  //lcd_show_text_vmks(); // Show hardcoded text "VMKS"
  //lcd_show_char('T'); lcd_show_char('U'); lcd_show_char('E'); lcd_show_char('S');
  lcd_show_text("VMKS", 4); // This is actually String object converting to char array but works for the demo
}

void loop() {
  delay(5000);
  lcd_cmd(B0000, 0); lcd_cmd(B0001, 0); delayMicroseconds(5*1530); // clear display - set all characters to space(' ') and return home
  lcd_set_cursor(6, 1);
  lcd_show_text_vmks();
  lcd_set_cursor(6, 2);
  lcd_show_char('T'); lcd_show_char('U'); lcd_show_char('E'); lcd_show_char('S');
  while (1) {};
}

void lcd_init(void) {
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
  lcd_cmd(B0000, 0); lcd_cmd(B0001, 0); delayMicroseconds(5*1530); // clear display - set all characters to space(' ') and return home
  lcd_cmd(B0000, 0); lcd_cmd(B1100, 0); delayMicroseconds(5*39);   // turn display on
}

// There is no parameter validation
// COL and ROW start from 1
void lcd_set_cursor(uint8_t col, uint8_t row) {
  uint8_t row_offset[2] = {0x00, 0x40};
  uint8_t pos = (col) + row_offset[row - 1];
  pos = (pos & 0x7F) | 0x80; // Add cursor position change command code
  uint8_t upper = (pos & 0xF0) >> 4;
  uint8_t lower = (pos & 0x0F) >> 0;
  lcd_cmd(upper, 0); lcd_cmd(lower, 0); delayMicroseconds(5*39); // set DDRAM address
}

// Send ASCII char
void lcd_show_char(char chr) {
  uint8_t upper = ((uint8_t)chr & 0xF0) >> 4;
  uint8_t lower = ((uint8_t)chr & 0x0F) >> 0;

  lcd_cmd(upper, 1); lcd_cmd(lower, 1); delayMicroseconds(5*43); // write data to DDRAM
}

// Send ASCII text
void lcd_show_text(char *text, uint8_t len) {
  for (uint8_t cnt = 0; cnt < len; cnt++) {
    lcd_show_char(text[cnt]);
  }
}

// Send hardcoded ASCII text "VMKS"
void lcd_show_text_vmks(void) {
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
