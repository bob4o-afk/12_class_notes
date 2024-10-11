volatile uint16_t var = 0;

void setup()
{
	// Забраняваме глобално прекъсванията
	noInterrupts(); //cli();
	
	// Зануляване на конфигурацията
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1B = 0;
	TIMSK1 = 0;
	TIFR1 = 0xFF;
	
	// Режим на таймера - 14 Fast-PWM
	TCCR1A = TCCR1A | (1 << WGM11);
	TCCR1B = TCCR1B | (1 << WGM12);
	TCCR1B = TCCR1B | (1 << WGM13);
	// TCCR1A |= (1 << WGM11);
	// TCCR1B = TCCR1B | (1 << WGM12) | (1 << WGM13);
	
	// Режим на изводите - неинв.
	TCCR1A = TCCR1A | (1 << COM1A1) | (1 << COM1B1);
	
	// Честота - 500Hz
	// Избираме Prescaler = 1
	ICR1 = 31999; // TOP = 16MHZ/(1*500Hz)-1 = 31999
	
	// Коеф. на запълване - 75%
	OCR1A = 23999; // DUTY = TOP * 75% = 31999*75% = 23999
	
	// Прекъсване - CM A
	TIMSK1 |= (1 << OCIE1A);
	
	// Пускане на таймера
	TCCR1B |= (1 << CS10);
	
	 // Разрешаваме глобално прекъсванията
	interrupts(); //sei();
}

ISR(TIMER1_COMPA_vect)
{
	var++;
}

void loop()
{}
