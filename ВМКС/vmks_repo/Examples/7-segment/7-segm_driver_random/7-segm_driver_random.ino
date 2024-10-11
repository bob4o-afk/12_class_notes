#include <stdlib.h>

#define DATA1_PIN		8
#define DATA2_PIN		9
#define DATA3_PIN		10
#define DATA4_PIN		11
#define LATCH0_PIN		12
#define LATCH1_PIN		13
#define LATCH2_PIN		7
#define LATCH3_PIN		5
#define LATCH4_PIN		4
#define LATCH5_PIN		A5
#define BLANKING_PIN	6

#define BUTTON_PIN		3
#define POT_PIN			A4
#define NC_PIN			A3

#define DIGITS			6
#define BRIGHTNESS		200		// Maximum 255

const uint8_t data_pins[4] = {DATA1_PIN, DATA2_PIN, DATA3_PIN, DATA4_PIN};
const uint8_t latch_pins[DIGITS] = {LATCH0_PIN, LATCH1_PIN, LATCH2_PIN, LATCH3_PIN, LATCH4_PIN, LATCH5_PIN};

volatile uint32_t current_value = 0;

void button_ISR(void);
void print_7segm(uint32_t val);

void setup()
{
	pinMode(NC_PIN, INPUT);
	uint16_t seed = analogRead(NC_PIN);
	Serial.begin(9600);
	Serial.print("PRNG seed: ");
	Serial.println(seed);
	srandom(seed);
  
	for (uint8_t i = 0; i < 4; i++)
	{
		digitalWrite(data_pins[i], LOW);
		pinMode(data_pins[i], OUTPUT);
	}
	for (uint8_t i = 0; i < DIGITS; i++)
	{
		digitalWrite(latch_pins[i], HIGH);
		pinMode(latch_pins[i], OUTPUT);
	}
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_ISR, FALLING);
	pinMode(BLANKING_PIN, OUTPUT);
	analogWrite(BLANKING_PIN, BRIGHTNESS);
}

void loop()
{
	print_7segm(current_value);
	delay(10);
}

void button_ISR(void)
{
	current_value = random();
	current_value |= ((uint32_t) random() << 16);
	Serial.print(current_value);
}

void print_7segm(uint32_t val)
{
	uint8_t i, j;
	uint8_t digit;
	
	for (i = 0; i < DIGITS; i++)
	{
		digit = val % 10;
		val /= 10;
		
		/*
		for (j = 0; j < 4; j++)
		{
			digitalWrite(data_pins[j], digit & (1 << j));
		}
		*/
		PORTB = (PORTB & 0xF0) | digit;
	  
		digitalWrite(latch_pins[DIGITS - i - 1], LOW);
		delayMicroseconds(1);
		digitalWrite(latch_pins[DIGITS - i - 1], HIGH);
		delayMicroseconds(1);
	}
}