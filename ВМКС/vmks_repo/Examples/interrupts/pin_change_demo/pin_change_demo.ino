volatile bool change_detected = false;

void setup()
{
	// Configure pins PC0, PC1, PC2 and PC3 (A0, A1, A2 and A3) as inputs
	DDRC &= ~((1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3));
	// Enable the built-in pull-up resistors for the same pins
	PORTC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);
	// Configure these pins to generate group 1 pin change interrupt
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);
	// Enable the group 1 pin change interrupt
	PCICR |= (1 << PCIE1);
	Serial.begin(38400, SERIAL_8E2);
}

void loop()
{
	if (change_detected)
	{
		// Software debounce of contact bounce
		delay(100);
		Serial.print("Switch changed: ");
		// Read the DIP switch and send the new value over UART
		Serial.println(PINC & ((1 << PINC0) | (1 << PINC1) | (1 << PINC2) | (1 << PINC3)), BIN);
		change_detected = false;
	}
}

ISR(PCINT1_vect)
{
	change_detected = true;
}
