void setup() {
  // put your setup code here, to run once:
  // pinMode(A0, OUTPUT);
  // pinMode(A1, OUTPUT);
  // pinMode(A2, OUTPUT);
  // pinMode(A3, OUTPUT);

  DDRC |= (1111 << DDC0);

  // DDRC |= (1 << DDC0);
  // DDRC |= (1 << DDC1);
  // DDRC |= (1 << DDC2);
  // DDRC |= (1 << DDC3);

  delay(100);
}

void loop() {
  // digitalWrite(A0, HIGH);
  // digitalWrite(A1, HIGH);
  // digitalWrite(A2, HIGH);
  // digitalWrite(A3, HIGH);

  PORTC |= (1111 << PORTC0);
  // PORTC |= (1 << PORTC0);  
  // PORTC |= (1 << PORTC1);  
  // PORTC |= (1 << PORTC2);  
  // PORTC |= (1 << PORTC3);  


  delay(1000);

  // digitalWrite(A0, LOW);
  // digitalWrite(A1, LOW);
  // digitalWrite(A2, LOW);
  // digitalWrite(A3, LOW);

  PORTC &= ~(1111 << PORTC0);   //here for me it was A4 that was working not A3
  // PORTC &= ~(1 << PORTC0);  
  // PORTC &= ~(1 << PORTC1);  
  // PORTC &= ~(1 << PORTC2);  
  // PORTC &= ~(1 << PORTC3); 

  delay(1000);
}
