#include <SPI.h>

#define INPUT_PIN	A0
#define CS_PIN    53

#define WRITE_CMD	((uint16_t) 0x00)
#define INCR_CMD	((uint16_t) 0x01)
#define DECR_CMD	((uint16_t) 0x02)
#define READ_CMD	((uint16_t) 0x03)

#define WIPER0_ADDR	((uint16_t) 0x00)
#define WIPER1_ADDR	((uint16_t) 0x01)

#define ADDR_OFFSET	12U
#define CMD_OFFSET	10U

#define POT_MIN		0U
#define POT_MAX		256U

void setup()
{
	pinMode(INPUT_PIN, INPUT);
	SPI.begin();
}

void loop()
{
  uint16_t pot_val = map(analogRead(INPUT_PIN), 0, 1023, 0, 256);
	SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CS_PIN, LOW);
	SPI.transfer16(WRITE_CMD << CMD_OFFSET | WIPER0_ADDR << ADDR_OFFSET | pot_val);
  SPI.transfer16(WRITE_CMD << CMD_OFFSET | WIPER1_ADDR << ADDR_OFFSET | pot_val);
  digitalWrite(CS_PIN, HIGH);
	SPI.endTransaction();
	delay(5);
}
