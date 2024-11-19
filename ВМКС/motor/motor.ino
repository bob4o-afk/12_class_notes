const int potPin = A0;
const int pwmPin = 9;
const int pwm2Pin = 8;


void setup() {
  pinMode(potPin, INPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(7, INPUT_PULLUP);
}

void loop() {
  int potValue = analogRead(potPin);
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  if(digitalRead(7)){
    analogWrite(pwmPin, pwmValue);
    digitalWrite(pwm2Pin, LOW);
  }
  else{
    analogWrite(pwm2Pin, pwmValue);
    digitalWrite(pwmPin, LOW);
  
  }
  delay(50);
}
