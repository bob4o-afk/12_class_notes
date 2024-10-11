#include <LiquidCrystal.h>

#define RS	12
#define EN	11
#define D4	5
#define D5	4
#define D6	3
#define D7	2

#define COLS 16
#define ROWS 2

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

byte minecraft[] = {
  B00000,
  B00110,
  B01000,
  B10100,
  B10010,
  B00001,
  B00000,
  B00000
};

byte body[] = {
  B00101,
  B00110,
  B11100,
  B00100,
  B00100,
  B01010,
  B10001,
  B00000
};

void setup()
{
  delay(40); // LCD Power-On Reset (POR) initialization wait
  lcd.createChar(0, smiley);
  lcd.createChar(1, body);
  lcd.createChar(2, minecraft);
  lcd.begin(COLS, ROWS);
  lcd.write(byte(0)); // Cast is needed for index 0 to prevent error
  lcd.write(2);
  lcd.setCursor(0, 1);
  lcd.write(1);
}

void loop()
{
}
