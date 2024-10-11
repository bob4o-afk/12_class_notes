#include <LiquidCrystal.h>
#include <string.h>

#define SCROLL_DELAY 250
#define LINE_DELAY 700

#define RS	12
#define EN	11
#define D4	5
#define D5	4
#define D6	3
#define D7	2

#define COLS 16
#define ROWS 2

char *text[] =
{
	"LOREM IPSUM",
	"qwertyuiop[",
	"the quick brown fox jumped over the lazy dog"
};

LiquidCrystal LCD_screen(RS, EN, D4, D5, D6, D7);

void setup()
{
	delay(40); // LCD Power-On Reset (POR) initialization wait
	LCD_screen.begin(COLS, ROWS);
	LCD_screen.clear();
}

void loop()
{
	uint8_t text_n;
	int8_t position;
	uint16_t i, j;
	uint16_t l;
	uint16_t print_size;
	
	// Not necesarily the best implementation, feel free to submit a PR
	for (text_n = 0; text_n < 3; text_n++)
	{
		l = strlen(text[text_n]);

		for (position = COLS - 1; position >= 0; position--)
		{
			LCD_screen.setCursor(position, 0);
			print_size = l;
			if (print_size > COLS - position)
			{
				print_size = COLS - position;
			}
			for (i = 0; i < print_size; i++)
			{
				LCD_screen.write(text[text_n][i]);
			}
			delay(SCROLL_DELAY);
			LCD_screen.clear();
		}

		for (j = 0; j < l; j++)
		{
			print_size = l - j;
			if (print_size > COLS)
			{
				print_size = COLS;
			}
			for (i = 0; i < print_size; i++)
			{
				LCD_screen.write(text[text_n][j + i]);
			}
			delay(SCROLL_DELAY);
			LCD_screen.clear();
		}

		delay(LINE_DELAY);
	}
}
