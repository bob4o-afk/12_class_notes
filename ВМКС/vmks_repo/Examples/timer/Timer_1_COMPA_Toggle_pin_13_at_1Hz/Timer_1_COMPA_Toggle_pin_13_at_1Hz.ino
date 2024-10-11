/*
	 Timer 1 is set to generate Compare Match Interrupt with frequency 1Hz
	 The counter counts with frequency 16MHz/1024 = 15.625kHz
	 For 1s the counter will reach value of [15.625kHz*1s - 1] = [15625 - 1] = 15624
	 This value is set as compare value so that when counter reaches it
	 it will generate Interrupt with Period exactly 1s => Frequency 1Hz
	 LED attached on pin 13 is TOGGLED with this frequency of 1Hz so it stays 1s on and 1s off
*/

volatile boolean toggle = 0;

void setup()
{
	// Set pin 13 as output
	pinMode(13, OUTPUT);
	// Stop reception of interrupts
	noInterrupts(); //cli();

	// Set Timer 1 Control registers and counter to 0
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1B = 0;
	TIMSK1 = 0;
	TIFR1 = 0xFF;

	// Set compare match value = Fclk_io / (Fout * Prescaler) - 1
	OCR1A = 15624; // = (16MHz) / (1 * 1024) - 1
	// Enable compare match interrupt
	TIMSK1 |= (1 << OCIE1A);

	// Set Timer 1 Mode of operation to Clear Timer on Compare Match (CTC -> Mode 4)
	TCCR1B |= (1 << WGM12); // Mode 4

	// Set Timer 1 Clock prescaler and source so that the timer starts counting
	TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024 (=> enable the clock)

	// Allow reception of interrupts
	interrupts(); //sei();
}

void loop()
{}

/*
	Timer1 Interrupt Service Routine (ISR)
	Toggle pin 13 (LED) every 1s
	Generates pulse wave of frequency 1Hz/2 = 0.5Hz
	Takes two cycles for full wave - toggle high then after 1s toggle low after 1s repeat
*/
ISR(TIMER1_COMPA_vect)
{
	if (toggle == 1)
	{
		digitalWrite(13, HIGH);
		toggle = 0;
	}
	else
	{
		digitalWrite(13, LOW);
		toggle = 1;
	}
}
