#define LED 12
#define BTN 2

// Define interrupt flag variable - must be volatile
//volatile uint8_t state = 1;

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(BTN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN), ISR_Task, FALLING);
}

void loop() {
  /*
  // Read the interrupt flag and do something
  if(state == 1)
  {
      digitalWrite(LED, !digitalRead(LED));
      delay(100);
      state = 0;
  }
  */
}

// Handler for the INT0 external interrupt
void ISR_Task() {
  //state = 1;    // Better to only set a flag so that the ISR is short and fast
  //delay(2000);  // Show that delay doesn't work
  digitalWrite(LED, !digitalRead(LED));
}
