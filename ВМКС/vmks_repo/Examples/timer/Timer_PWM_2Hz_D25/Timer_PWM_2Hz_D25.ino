// Timer 1 - Mode 14
// f = 2Hz ; δ = 25%

void setup()
{
	// Configure the OC1A pin as an output
	DDRB |= (1 << PB1);

	// Zero
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 = 0;
	OCR1B = 0;
	TIFR1 = 0xFF;

	// Set timer mode and output mode
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	ICR1 = 31249; // Period (TOP)
	OCR1A = 7812; // Duty cycle
	// Activate the timer by selecting the clock source
	TCCR1B |= (1 << CS12);
}

void loop()
{}
