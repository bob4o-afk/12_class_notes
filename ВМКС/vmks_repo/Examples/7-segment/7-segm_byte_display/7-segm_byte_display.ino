#include <math.h>

#define SW0_PIN	 A0
#define SW1_PIN	 A1
#define SW2_PIN	 A2
#define SW3_PIN	 A3
#define SW4_PIN	 A4
#define SW5_PIN	 A5
#define SW6_PIN	 2
#define SW7_PIN	 3

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

#define DIGITS	 2

int print_digit(uint8_t position, uint8_t digit);
void emulate_timer_ISR(void);
uint8_t read_sw_slow(void);
uint8_t read_sw(void);

const uint8_t segm_pins[8] = {A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, F_PIN, G_PIN, DP_PIN};
const uint8_t en_pins[DIGITS] = {EN0_PIN, EN1_PIN};
const uint8_t sw_pins[8] = {SW0_PIN, SW1_PIN, SW2_PIN, SW3_PIN, SW4_PIN, SW5_PIN, SW6_PIN, SW7_PIN};

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
		pinMode(sw_pins[i], INPUT_PULLUP);
	}
}

void loop()
{
	uint8_t switch_val = read_sw();
	print_digit(0, switch_val >> 4);
	print_digit(1, switch_val & 0x0F);

	// This is garbage, don't use it!
	for(uint8_t i = 0; i < 10; i++)
	{
		delay(10);
		emulate_timer_ISR();
	}
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

uint8_t read_sw_slow(void)
{
	uint8_t switch_value = 0;
	
	for (uint8_t i = 0; i < 8; i++)
	{
		switch_value += !digitalRead(sw_pins[i]) << i;
	}

	return switch_value;
}

uint8_t read_sw(void)
{
	return (~PINC & 0x3F) | ((~PIND & 0x0C) << 4);
}
