#define Y_U_SO_SLOW

void setup()
{
	#ifdef Y_U_SO_SLOW
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	digitalWrite(8, LOW);
	digitalWrite(9, LOW);
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	#else
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
	PORTB = (PORTB | (1 << DDB2) | (1 << DDB3)) & ~((1 << DDB0) | (1 << DDB1));
	#endif
}

void loop()
{
	#ifdef Y_U_SO_SLOW
	delay(100);
	digitalWrite(8, HIGH);
	digitalWrite(9, HIGH);
	digitalWrite(10, LOW);
	digitalWrite(11, LOW);
	delayMicroseconds(50);
	digitalWrite(8, LOW);
	digitalWrite(9, LOW);
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	#else
	PORTB ^= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
	delayMicroseconds(50);
	PORTB ^= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
	delay(100);
	#endif
}
