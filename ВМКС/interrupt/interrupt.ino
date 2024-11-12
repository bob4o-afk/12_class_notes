void button_pressed_ISR(void);

volatile uint8_t ledState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), button_pressed_ISR, FALLING);
}

void loop() {
  
  if (ledState){
    Serial.println("Nigger");
  }

  delay(5000);
  // put your main code here, to run repeatedly:

}


void button_pressed_ISR (){
  if(ledState){
    ledState = 0;
    digitalWrite(13, HIGH);
    Serial.println("nigger");
  }else{
    ledState = 1;
    digitalWrite(13, LOW);

  }
}