#include <Wire.h>

#define MASTER_INT_PIN	A2
#define INT_PIN	3
#define SW0_PIN	7
#define SW1_PIN	6
#define SW2_PIN	5
#define SW3_PIN	4

#define SLAVE_ADDRESS	0x0A

void i2c_send_handler(void);
void button_handler(void);

volatile uint8_t dip_sw = 0;
volatile bool new_data = false;

void setup()
{
	pinMode(MASTER_INT_PIN, OUTPUT);
	digitalWrite(MASTER_INT_PIN, LOW);
	pinMode(INT_PIN, INPUT_PULLUP);
	pinMode(SW0_PIN, INPUT_PULLUP);
	pinMode(SW1_PIN, INPUT_PULLUP);
	pinMode(SW2_PIN, INPUT_PULLUP);
	pinMode(SW3_PIN, INPUT_PULLUP);

	attachInterrupt(digitalPinToInterrupt(INT_PIN), button_handler, FALLING);

	Wire.begin(SLAVE_ADDRESS);
	Wire.onRequest(i2c_send_handler);

	Serial.begin(9600);
}

void loop()
{
	uint8_t tmp = digitalRead(SW0_PIN) |
				 (digitalRead(SW1_PIN) << 1) |
				 (digitalRead(SW2_PIN) << 2) |
				 (digitalRead(SW3_PIN) << 3);
	dip_sw = tmp;
	if (new_data)
	{
		new_data = false;
		digitalWrite(MASTER_INT_PIN, HIGH);
		delayMicroseconds(5);
		digitalWrite(MASTER_INT_PIN, LOW);
		delayMicroseconds(5);
	}
}

void i2c_send_handler(void)
{
	Wire.write((uint8_t *) &dip_sw, sizeof(dip_sw));
}

void button_handler(void)
{
	new_data = true;
}
