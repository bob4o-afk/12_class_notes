#define BTN_PIN  2
#define LED_PIN 13

void button_pressed_ISR(void);
void slow_computation(void);

volatile uint8_t led_state = 0;

void setup()
{
    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_pressed_ISR, FALLING);
    //attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_pressed_ISR, RISING);
    //attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_pressed_ISR, CHANGE);
  
    Serial.begin(9600);
}

void loop()
{
    slow_computation();
    
    if (led_state)
    Serial.println("LED in on.");
    else
    Serial.println("LED in off.");
}

void button_pressed_ISR(void)
{
    if (led_state)
  {
    led_state = 0;
    digitalWrite(LED_PIN, LOW);
  }
  else
  {
    led_state = 1;
    digitalWrite(LED_PIN, HIGH);
  }
}

void slow_computation(void)
{
    delay(5000);
}
