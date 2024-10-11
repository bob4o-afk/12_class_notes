void setup()
{
	DDRB |= (1 << DDB5);       // Set digital pin 13 (Port B Pin 5) to output
}

void loop()
{
	PORTB |= (1 << PORTB5);    // Set digital pin 13 (Port B Pin 5) high
	delay(500);                // wait 500ms
	PORTB &= ~(1 << PORTB5);   // Set digital pin 13 (Port B Pin 5) low
	delay(500);                // wait 500ms

	//PORTB ^= (1 << PORTB5);  // Toggle digital pin 13 (Port B Pin 5)
}
