#include <LiquidCrystal.h>

#define UP_PIN	 3
#define DOWN_PIN 2

#define RS_PIN	12
#define EN_PIN	11
#define D4_PIN	7
#define D5_PIN	6
#define D6_PIN	5
#define D7_PIN	4

#define COLUMNS	16
#define ROWS	2

void counter_up(void);
void counter_down(void);

LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
volatile uint8_t counter = 0;

void setup()
{
	delay(40); // LCD Power-On Reset (POR) initialization wait
	lcd.begin(COLUMNS, ROWS);
	pinMode(UP_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(UP_PIN), counter_up, FALLING);
	pinMode(DOWN_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(DOWN_PIN), counter_down, FALLING);
}

void loop()
{
	lcd.setCursor(7, 0);
	lcd.print(counter);
}

void counter_up(void)
{
	counter++;
}

void counter_down(void)
{
	counter--;
}
