#define BTN 2
#define LED 5

byte stateON = false;
uint8_t count = 0;

void setup()
{
  pinMode(BTN, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  if(digitalRead(BTN) == 0)
  {
    stateON = true;
  }
  
  if(stateON == true)
  {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
    count++;
    if(count >= 5)
    {
      stateON = false;
    }
  }
}
