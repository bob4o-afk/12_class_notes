#include <math.h>

#define A_PIN	 12
#define B_PIN	 13
#define C_PIN	 7
#define D_PIN	 8
#define E_PIN	 9
#define F_PIN	 11
#define G_PIN	 10
#define DP_PIN	 6
#define EN0_PIN	 5
#define EN1_PIN	 4
#define UP_PIN	 3
#define DOWN_PIN 2

#define DIGITS	 2

int print_dec(uint16_t value);
int print_digit(uint8_t position, uint8_t digit);
void emulate_timer_ISR(void);
void counter_up(void);
void counter_down(void);

const uint8_t segm_pins[8] = {A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, F_PIN, G_PIN, DP_PIN};
const uint8_t en_pins[DIGITS] = {EN0_PIN, EN1_PIN};

const uint8_t segment_map[16] =
{
	// A B C D E F G DP
	0b00000011,	// 0
	0b10011111,	// 1
	0b00100101,	// 2
	0b00001101,	// 3
	0b10011001,	// 4
	0b01001001,	// 5
	0b01000001,	// 6
	0b00011111,	// 7
	0b00000001,	// 8
	0b00001001,	// 9
	0b00010001,	// A
	0b11000001,	// b
	0b01100011,	// C
	0b10000101,	// d
	0b01100001,	// E
	0b01110001	// F
};

volatile uint8_t display_value[DIGITS] = {0};
volatile uint8_t current_digit = 0;
volatile uint8_t counter = 0;

void setup()
{
	uint8_t i;
	for (i = 0; i < DIGITS; i++)
	{
		pinMode(en_pins[i], OUTPUT);
		digitalWrite(en_pins[i], HIGH);
	}
	for (i = 0; i < 8; i++)
	{
		pinMode(segm_pins[i], OUTPUT);
		digitalWrite(segm_pins[i], HIGH);
	}
	pinMode(UP_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(UP_PIN), counter_up, FALLING);
	pinMode(DOWN_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(DOWN_PIN), counter_down, FALLING);
}

void loop()
{
	print_dec(counter);

	// This is garbage, don't use it!
	for(uint8_t i = 0; i < 10; i++)
	{
		delay(10);
		emulate_timer_ISR();
	}
}

int print_dec(uint16_t value)
{
	if (value > (int) pow(10, DIGITS) - 1)
	{
		return -1;
	}

	for (uint8_t i = 0; i < DIGITS; i++)
	{
		print_digit(DIGITS - 1 - i, value % 10);
		value /= 10;
	}

	return 0;
}

int print_digit(uint8_t position, uint8_t digit)
{
	if (position > DIGITS - 1 || digit > 15)
	{
		return -1;
	}

	display_value[position] = digit;

	return 0;
}

void emulate_timer_ISR(void)
{
	digitalWrite(en_pins[current_digit], HIGH);

	current_digit++;
	if (current_digit > DIGITS - 1)
	{
		current_digit = 0;
	}

	for (uint8_t i = 0; i < 8; i++)
	{
		digitalWrite(segm_pins[i], segment_map[display_value[current_digit]] & (128 >> i));
	}

	digitalWrite(en_pins[current_digit], LOW);
}

void counter_up(void)
{
	counter++;
}

void counter_down(void)
{
	counter--;
}
