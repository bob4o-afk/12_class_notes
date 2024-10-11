void setup()
{
	// Set pin 13 to output
	pinMode(13, OUTPUT);
	
	// Stop reception of interrupts
	noInterrupts(); //cli();

	// Set PB1 to be an output (Pin-9 Arduino UNO; OC1A)
	DDRB |= (1 << PB1);
	
	// Clear Timer/Counter Control Registers
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 = 0;
	TIFR1 = 0xFF;
	
	// Set non-inverting mode - Table 15-3 (page 108)
	TCCR1A |= (1 << COM1A1);
	
	// Set Fast-PWM Mode (Mode 14) - Table 15-5 (page 109)
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);
	
	// Clear Timer 1 Counter
	TCNT1  = 0;
	
	// Set PWM frequency/top value - Output PWM 10kHz
	ICR1 = 199;		// Fclk_io / (Fout * Prescaler) - 1
	OCR1A = 100;	// Output OC1A will be ON for [OCR1A/(ICR1+1)]% of the time -> 100/(199+1) = 50%
	OCR1B = 50;
	
	// Enable compare match and overflow interrupts
	TIMSK1 |= (1 << OCIE1A);
	TIMSK1 |= (1 << OCIE1B);
	TIMSK1 |= (1 << TOIE1);
	
	// Set prescaler to 8 and starts PWM
	TCCR1B |= (1 << CS11);

	// Enables interrupts
	interrupts(); //sei();
}

void loop()
{
	// Empty
}

// NOTE: TinkerCAD does not simulate timer interrupts correctly when
// something is connected to the timer pins.

// Not used, just demonstrating how to define it
ISR(TIMER1_COMPA_vect)
{
	// Empty
}

//Timer1 Compare Match Interrupt turns OFF pin 13 (LED)
ISR(TIMER1_COMPB_vect)
{
	digitalWrite(13, LOW);
}

//Timer1 Overflow Interrupt turns ON pin 13 (LED)
ISR(TIMER1_OVF_vect)
{
	digitalWrite(13, HIGH);
}
