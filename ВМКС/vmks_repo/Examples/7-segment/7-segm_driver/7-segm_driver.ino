#define DATA1_PIN		2
#define DATA2_PIN		5
#define DATA3_PIN		4
#define DATA4_PIN		3
#define LATCH1_PIN		9
#define LATCH2_PIN		8
#define LATCH3_PIN		7
#define LATCH4_PIN		6
#define BLANKING_PIN	10

#define BRIGHTNESS		200		// Maximum 255

int print_digit(uint8_t position, uint8_t digit);
void pulse_pin(uint8_t pin);

const uint8_t data_pins[4] = {DATA1_PIN, DATA2_PIN, DATA3_PIN, DATA4_PIN};
const uint8_t latch_pins[4] = {LATCH1_PIN, LATCH2_PIN, LATCH3_PIN, LATCH4_PIN};

void setup()
{
	for (uint8_t i = 0; i < 4; i++)
	{
		pinMode(data_pins[i], OUTPUT);
		digitalWrite(data_pins[i], LOW);
		pinMode(latch_pins[i], OUTPUT);
		digitalWrite(latch_pins[i], HIGH);
	}
	pinMode(BLANKING_PIN, OUTPUT);
	analogWrite(BLANKING_PIN, BRIGHTNESS);
}

void loop()
{
	print_digit(0, 7);
	print_digit(1, 7);
	print_digit(2, 3);
	print_digit(3, 4);
	delay(1000);
}

int print_digit(uint8_t position, uint8_t digit)
{
	if (position > 3 || digit > 15)
	{
		return -1;
	}
	
	// Encode the digit on the four data signals to the drivers
	for (uint8_t i = 0; i < 4; i++)
	{
		digitalWrite(data_pins[i], digit & (1 << i));
	}
	// Latch the data
	pulse_pin(latch_pins[position]);

	return 0;
}

void pulse_pin(uint8_t pin)
{
	// The delay from calling digitalWrite() is enough to satisfy the
	// setup and hold times of CD5411 but we delay some more for good measure.
	delayMicroseconds(5);
	digitalWrite(pin, LOW);
	delayMicroseconds(5);
	digitalWrite(pin, HIGH);
} 
