#include <Wire.h>

#define INT_PIN	2

#define SLAVE_ADDRESS	0x09

size_t i2c_write(uint8_t address, void *data, size_t size);
size_t i2c_read(uint8_t address, void *data, size_t size);
void slave_interrupt(void);

volatile bool new_data = false;

void setup()
{
	Wire.begin();
	Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(INT_PIN), slave_interrupt, RISING);
}

void loop()
{
	uint8_t dip_sw;

	if (new_data)
	{
		i2c_read(SLAVE_ADDRESS, &dip_sw, sizeof(dip_sw));
		Serial.println(dip_sw);
		new_data = false;
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

void slave_interrupt(void)
{
	new_data = true;
}