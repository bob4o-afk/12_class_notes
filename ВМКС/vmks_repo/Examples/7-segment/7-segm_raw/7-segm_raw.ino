#define A_PIN	8
#define B_PIN	9
#define C_PIN	3
#define D_PIN	4
#define E_PIN	5
#define F_PIN	7
#define G_PIN	6
#define DP_PIN	2

int print_digit(uint8_t digit);

const uint8_t pins[8] = {A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, F_PIN, G_PIN, DP_PIN};

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

void setup()
{
	for (uint8_t i = 0; i < 8; i++)
	{
		pinMode(pins[i], OUTPUT);
		digitalWrite(pins[i], HIGH);
	}
}

void loop()
{
	for (uint8_t cnt = 0; cnt < 16; cnt++)
	{
		print_digit(cnt);
		delay(1000);
	}
}

int print_digit(uint8_t digit)
{
	if (digit > 15)
	{
		return -1;
	}

	for (uint8_t i = 0; i < 8; i++)
	{
		digitalWrite(pins[i], segment_map[digit] & (128 >> i));
	}

	return 0;
}
