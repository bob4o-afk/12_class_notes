#define LDR A0

uint16_t value = 0;

void setup()
{
	pinMode(LDR, INPUT);
	Serial.begin(38400, SERIAL_8E2);
}

void loop()
{
	value = analogRead(LDR);
	Serial.println(value);
	delay(100);
}
