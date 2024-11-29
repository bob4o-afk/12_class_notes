volatile byte state = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);         //pin za OC1A
  pinMode(10, OUTPUT);        //pin za OC1B
  pinMode(13, OUTPUT);        //13 prosto zashotot dolu go imame
  noInterrupts();

  TCCR1A = 0;     //zanulqvame register A
  TCCR1B = 0;     //zanulqvame register B
  TIMSK1 = 0;     //zanulqvame tova koeto pozvolqva prekusvaniqta  
  TCNT1 = 0;      //zanulqvame count

  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);    //tuka se kopvat

  ICR1 = 727;       //tova se iz4islqva ot TOP formulata kato v momenta dolu e 22kHz, a gore e 16kHz a N si e 1

  OCR1A = 546;      //tova e 75% PWM
  // OCR1B = 73;       //tova e 10%
  OCR1B = 146;       //tova e 20% za kanal B

  TCCR1A |= (1 << COM1A1);
  TCCR1A |= (1 << COM1B1);    //tuka i dvete trqvba da se zadadat na 1 a COM1A0 i COM1B0  sa si 0 i trqbva da si e taka


  TIMSK1 |= (1 << TOIE1);     //Bit 0 – TOIE1: Timer/Counter1, Overflow Interrupt Enable  (tova gornoto deto zanulih sega vdigam samo tozi pin)
  TCCR1B |= (1 << CS10);      // clocka

  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:

}


ISR(TIMER1_OVF_vect){       //pri overflow
  digitalWrite(13, state);      
  state = !state;     //trqbva da e volatile za da moje ne se prenebregva
}
