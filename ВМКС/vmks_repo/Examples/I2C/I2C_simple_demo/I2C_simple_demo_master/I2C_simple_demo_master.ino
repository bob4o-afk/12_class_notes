#include <Wire.h>

#define SLAVE_ADDRESS	0x09
#define DELAY_TIME 		200

size_t i2c_write(uint8_t address, void *data, size_t size);
size_t i2c_read(uint8_t address, void *data, size_t size);

void setup()
{
	Wire.begin();
	Serial.begin(9600);
}

void loop()
{
	static bool led_status = false;
	uint16_t pot_value = 0;

	Serial.print("Turning LED ");
	Serial.println(led_status ? "on": "off");
	i2c_write(SLAVE_ADDRESS, &led_status, sizeof(led_status));
	led_status = !led_status;
	
	i2c_read(SLAVE_ADDRESS, &pot_value, sizeof(pot_value));
	Serial.print("Received pot_value = ");
	Serial.println(pot_value);
	
	delay(DELAY_TIME);
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
