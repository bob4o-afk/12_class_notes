#define BTN_PIN 2

void btn_press(void);

uint8_t btn_cnt = 0;
uint8_t * ptr_a = &btn_cnt;

void setup()
{
  pinMode(BTN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), btn_press, FALLING);
  Serial.begin(9600);
}

void loop()
{
  while (1)
  {
    if (*ptr_a == 5)
    {
        Serial.println("TEST");
    }
  }
}

void btn_press(void)
{
  *ptr_a+=1;
}
