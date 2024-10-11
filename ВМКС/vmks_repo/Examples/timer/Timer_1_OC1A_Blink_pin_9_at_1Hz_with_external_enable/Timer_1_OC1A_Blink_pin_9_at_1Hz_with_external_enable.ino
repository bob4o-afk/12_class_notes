#define BTN_PIN		2

volatile uint8_t timer_en = 0;

void button_pressed_ISR(void);

// NOTE: TinkerCAD has some issues when simulating timers, it's better to run this on real hardware

void setup()
{
	// Stop reception of interrupts
	noInterrupts(); //cli();

	pinMode(BTN_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_pressed_ISR, FALLING);

	// Set PB1 to be an output (Pin9 Arduino UNO)
	DDRB |= (1 << PB1);

	// Clear Timer/Counter Control Registers
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1B = 0;
	TIMSK1 = 0;
	TIFR1 = 0xFF;

	// Set non-inverting mode - Table 15-3 (page 108)
	TCCR1A |= (1 << COM1A1);

	// Set Fast-PWM Mode (Mode 14) - Table 15-5 (page 109)
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);

	// Clear Timer 1 Counter
	TCNT1 = 0;

	// Set PWM frequency/top value - Output PWM 1Hz
	ICR1 = 15625;
	OCR1A = 10000;

	// Enable interrupts
	interrupts();
}

void loop()
{
	// some useless code here
}

void button_pressed_ISR(void)
{
	if (timer_en)
	{
		timer_en = 0;
		// Disable the timer by selecting "none" as the clock source
		TCCR1B &= ~((1 << CS11) | (1 << CS12) | (1 << CS10));
	}
	else
	{
		timer_en = 1;
		// Enable the timer
		TCCR1B |= (1 << CS12) | (1 << CS10);
		TCCR1B &= ~(1 << CS11);
	}
}
