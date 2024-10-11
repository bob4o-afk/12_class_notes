#define LED PB5 // LED is connected to digital pin 13
#define BTN PD2 // Button is connected to digital pin 2

void setup()
{
  // PB5 is OUTPUT
  DDRB |= (1 << PB5); //0b00100000; // 0x20;
  // PD2 is INPUT
  DDRD &= ~(1 << BTN);
  // PD2 PULLUP turn on
  PORTD |= (1 << BTN);

  cli();  // Disable Global Interrupts

  // Set INT0 mode to FALLING
  EICRA = 0;
  EICRA |= (1 << ISC01);
  // Enable INT0 interrupt
  EIMSK = 0;
  EIMSK |= (1 << INT0);

  sei();  // Enable Global Interrupts
}

void loop()
{
  // Empty
}

ISR(INT0_vect)
{
  PORTB ^= (1 << PB5);  // Toggle LED
}
