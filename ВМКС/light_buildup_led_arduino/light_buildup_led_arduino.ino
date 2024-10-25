void setup() {
  // put your setup code here, to run once:
  // DDRB   - celiq register e tova
  // DDB5 - dadeniq pin (v nashiq slu4ai si e 5 no se gleda dokumentaciq)
  DDRB |= (1 << DDB5);      //pinMode(13, OUTPUT)
  PORTB |= (1 << PORTB5);   //digitalWrite(13, HIGHT)
}

void loop() {
  // put your main code here, to run repeatedly:


  DDRB |= (1 << DDB5);      //pinMode(13, OUTPUT)
  PORTB |= (1 << PORTB5);   //digitalWrite(13, HIGHT)

  delay(1000);

  PORTB &= ~(1 << PORTB5); 

  delay(1000);

}
