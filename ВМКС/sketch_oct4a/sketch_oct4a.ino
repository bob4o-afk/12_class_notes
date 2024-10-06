  int hasBeenPressed = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  digitalWrite(9, LOW);

}

void loop() {
  // int isPressed = digitalRead(10);
  // if(!isPressed && hasBeenPressed==0){
  //   digitalWrite(9, HIGH);
  //   hasBeenPressed = 1;
  //   delay(1000);

  // }else if (!isPressed && hasBeenPressed==1) {
  //   digitalWrite(9, LOW);
  //   hasBeenPressed = 0;
  //   delay(1000);
  // }
  analogWrite(9, 50);
  delay(1000);
  analogWrite(9, 150);
  delay(1000);
}
