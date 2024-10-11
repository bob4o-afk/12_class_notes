#include <Wire.h>

#define INT_SLAVE1_PIN	3
#define INT_SLAVE2_PIN	2

#define SLAVE1_ADDRESS	0x09
#define SLAVE2_ADDRESS	0x0A

size_t i2c_write(uint8_t address, void *data, size_t size);
size_t i2c_read(uint8_t address, void *data, size_t size);
void slave1_interrupt(void);
void slave2_interrupt(void);

volatile bool new_data1 = false;
volatile bool new_data2 = false;

void setup()
{
	Wire.begin();
	Serial.begin(9600);
	pinMode(INT_SLAVE1_PIN, INPUT);
	pinMode(INT_SLAVE2_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(INT_SLAVE1_PIN), slave1_interrupt, RISING);
	attachInterrupt(digitalPinToInterrupt(INT_SLAVE2_PIN), slave2_interrupt, RISING);
}

void loop()
{
	uint8_t dip_sw;

	if (new_data1)
	{
		i2c_read(SLAVE1_ADDRESS, &dip_sw, sizeof(dip_sw));
		Serial.print("From slave 1: ");
		Serial.println(dip_sw);
		new_data1 = false;
	}
	if (new_data2)
	{
		i2c_read(SLAVE2_ADDRESS, &dip_sw, sizeof(dip_sw));
		Serial.print("From slave 2: ");
		Serial.println(dip_sw);
		new_data2 = false;
	}
}

size_t i2c_write(uint8_t address, void *data, size_t size)
{
	int error_code;
	size_t bytes_written;

	Wire.beginTransmission(address);
	bytes_written = Wire.write((uint8_t *) data, size);
	error_code =  Wire.endTransmission();

	return error_code ? 0: bytes_written;
}

size_t i2c_read(uint8_t address, void *data, size_t size)
{
	size_t bytes_received = Wire.requestFrom(address, size);

	if (bytes_received == size)
	{
		for (size_t i = 0; i < size; i++)
		{
			((uint8_t *) data)[i] = Wire.read();
		}
	}

	return bytes_received;
}

void slave1_interrupt(void)
{
	new_data1 = true;
}

void slave2_interrupt(void)
{
	new_data2 = true;
}