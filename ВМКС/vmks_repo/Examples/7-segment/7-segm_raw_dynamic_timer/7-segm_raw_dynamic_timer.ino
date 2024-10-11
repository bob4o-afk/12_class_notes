#include <math.h>

#define A_PIN	12
#define B_PIN	13
#define C_PIN	7
#define D_PIN	8
#define E_PIN	9
#define F_PIN	11
#define G_PIN	10
#define DP_PIN	6
#define EN0_PIN	5
#define EN1_PIN	4
#define EN2_PIN	3
#define EN3_PIN	2

#define DIGITS	4

int print_dec(uint16_t value);
int print_digit(uint8_t position, uint8_t digit);
void timer_init(void);
void gpio_init(void);

const uint8_t segm_pins[8] = {A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, F_PIN, G_PIN, DP_PIN};
const uint8_t en_pins[DIGITS] = {EN0_PIN, EN1_PIN, EN2_PIN, EN3_PIN};

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
	gpio_init();
	timer_init();
}

void loop()
{
	for (uint16_t cnt = (int) pow(10, DIGITS) - 1; cnt > 0; cnt--)
	{
		print_dec(cnt);
		delay(100);
	}
	delay(3000);
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
	if (position > DIGITS || digit > 15)
	{
		return -1;
	}

	display_value[position] = digit;

	return 0;
}

ISR(TIMER1_OVF_vect)
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

void gpio_init(void)
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
}

void timer_init(void)
{
	noInterrupts();
	
	// After clearing TCCR1B the timer is stopped
	TCCR1B = 0;
	TCNT1  = 0;
	
	TCCR1A = (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TIMSK1 = (1 << TOIE1);

	// Set frequency to 1kHz
	ICR1 = 1999;
	TCCR1B |= (1 << CS11);

	interrupts();
}
