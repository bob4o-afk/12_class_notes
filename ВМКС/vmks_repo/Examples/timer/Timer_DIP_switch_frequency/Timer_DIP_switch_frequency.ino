#define DIP_SW_0	8
#define DIP_SW_1	9
#define DIP_SW_2	10
#define DIP_SW_3	11

#define BUTTON		2
#define LED			13

void button_ISR(void);

void setup()
{
	pinMode(DIP_SW_0, INPUT_PULLUP);
	pinMode(DIP_SW_1, INPUT_PULLUP);
	pinMode(DIP_SW_2, INPUT_PULLUP);
	pinMode(DIP_SW_3, INPUT_PULLUP);
	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);

	attachInterrupt(digitalPinToInterrupt(BUTTON), button_ISR, FALLING);

	// Disable interrupts during timer configuration
	cli();

	// Zero the control and counter registers
	TCCR1A = TCCR1B = TIMSK1 = OCR1B = 0;
	TCNT1 = 0;
	TIFR1 = 0;

	// Select mode 15 (Fast PWM, TOP = OCR1A)
	TCCR1A |= (1 << WGM10);
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);

	// Set max counter value (frequency)
	OCR1A = 7811;

	// Enable timer overflow interrupt
	TIMSK1 |= (1 << TOIE1);

	// Set prescaler to 1024
	TCCR1B |= (1 << CS10) | (1 << CS12);

	// Enable interrupts
	sei();

	Serial.begin(9600);
}

void loop()
{
	Serial.println(OCR1A);
	delay(1000);
}

ISR(TIMER1_OVF_vect)
{
	static volatile bool led_flag = false;
	
	digitalWrite(LED, led_flag);
	led_flag = !led_flag;
}

void button_ISR(void)
{
	// Read the DIP switch
	uint8_t f = ~PINB & 0x0F;

	if (f)
	{
		// Convert frequency to OCR1A value
		OCR1A = 16000000 / (1024 * f) - 1;
	}
	// Instead of ignoring the case f == 0, you could also disable the timer
}
