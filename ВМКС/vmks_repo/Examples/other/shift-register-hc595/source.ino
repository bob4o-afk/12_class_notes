const uint8_t shreg_shcp_pin = 6;
const uint8_t shreg_input_pin = 5;
const uint8_t shreg_stcp_pin = 4;
const uint8_t shreg_pins[] = {
	shreg_input_pin,
	shreg_stcp_pin,
	shreg_shcp_pin
};

void setup()
{
	for (uint8_t i = 0; i < (sizeof(shreg_pins)/sizeof(shreg_pins[0])); ++i){
		pinMode(shreg_pins[i], OUTPUT);
	}
	
	digitalWrite(shreg_stcp_pin, LOW);
	digitalWrite(shreg_shcp_pin, LOW);
}

void shreg_write(uint8_t data) {
	for (uint8_t i = 0; i < 8; ++i) {
		digitalWrite(shreg_shcp_pin, LOW);
		uint8_t val = data & (0x80 >> i);
		digitalWrite(shreg_input_pin, val > 0);
		digitalWrite(shreg_shcp_pin, HIGH);
	}
	digitalWrite(shreg_shcp_pin, LOW);

	digitalWrite(shreg_stcp_pin, HIGH);
	digitalWrite(shreg_stcp_pin, LOW);
}

void loop()
{
	for (uint8_t i = 0; i < 8; ++i) {
		shreg_write(1 << i);
		delay(500);
	}
}
