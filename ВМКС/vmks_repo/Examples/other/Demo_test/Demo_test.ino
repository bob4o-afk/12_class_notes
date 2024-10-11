#include <Adafruit_NeoPixel.h>

#define LED_STRIP_PIN	12
#define SWITCH_PIN		2

#define IN1	5
#define IN2 6
#define EN	13
#define POT	A3

#define NUM_PIXELS		10

void button_pressed_ISR(void);

volatile uint8_t pixel_color = 0;
volatile uint16_t counter = 0;
Adafruit_NeoPixel led_strip(NUM_PIXELS, LED_STRIP_PIN, NEO_GRB);

void setup()
{
	pinMode(SWITCH_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), button_pressed_ISR, FALLING);
	pinMode(LED_STRIP_PIN, OUTPUT);
	led_strip.begin();

	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	digitalWrite(IN2, LOW);
	pinMode(EN, OUTPUT);
	digitalWrite(EN, HIGH);
	pinMode(POT, INPUT);

	noInterrupts();

	TCNT1  = 0;

	ICR1 = 311;
	OCR1B = 194;
	TIMSK1 = (1 << TOIE1);
	TCCR1A = (1 << WGM11) | (1 << COM1B1);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS12);

	interrupts();

	Serial.begin(9600);
}

void loop()
{
	if (pixel_color)
	{
		led_strip.setPixelColor(3, led_strip.Color(0, 255, 0));
	}
	else
	{
		led_strip.setPixelColor(3, led_strip.Color(255, 255, 255));
	}
	led_strip.show();
	delay(100);

	analogWrite(IN1, map(analogRead(POT), 0, 1023, 0, 255));
}

void button_pressed_ISR(void)
{
	pixel_color = !pixel_color;
}

ISR(TIMER1_OVF_vect)
{
	counter++;
}
