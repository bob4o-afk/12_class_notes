int photoPin = A6;
//+ -> +
//sig -> -
//- -> sig
//active - low

// void setup() {
//   Serial.begin(9600);
//   pinMode(photoPin, INPUT);

// }

// void loop() {
//   Serial.println(analogRead(photoPin));
//   delay(50);

// }

int ledPin = 12;
int buzzerPin = 11;
int buzzerButton = 10;

int button1Val = 0;

void setup () {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerButton, INPUT);
  digitalWrite(buzzerButton, HIGH);
  Serial.print("Starting");
}



void loop() {
  button1Val = digitalRead(buzzerButton);
  Serial.println(digitalRead(button1Val));
  if (button1Val == HIGH) {

    // digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, HIGH);

  } else {

    // digitalWrite(buzzerPin, HIGH);
  digitalWrite(ledPin, LOW);

  }
  // digitalWrite(ledPin, HIGH);
  // delay(1000);
  // tone(buzzerPin, 4000);
  // delay(1000);
}