#include <inttypes.h>

#define A1_PIN	9
#define A2_PIN	8
#define B1_PIN	11
#define B2_PIN	10
#define EN_PIN	12

#define STEP_TIME 200  // ms, max 1000

#define FULL_STEP
//#define HALF_STEP

#ifdef FULL_STEP
#define NUM_STEPS 4
const uint8_t coil_current[NUM_STEPS][4] =
{
	{1, 0, 0, 1}, 
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 1}
};
#endif

#ifdef HALF_STEP
#define NUM_STEPS 8
const uint8_t coil_current[NUM_STEPS][4] =
{
	{1, 0, 0, 1}, 
	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0}, 
	{0, 0, 1, 0},
	{0, 0, 1, 1},
	{0, 0, 0, 1}
};
#endif

void timer1_init(void);
void stepper_init(void);

const uint8_t stepper_pins[4] = {A2_PIN, A1_PIN, B1_PIN, B2_PIN};

void setup()
{
	stepper_init();
	timer1_init();
}

void loop()
{}

void timer1_init(void)
{
	// Disable interrupts during timer configuration
	noInterrupts();
	// Select CTC mode (4) and set the prescaler to divide the clock by 256
	// resulting in timer frequency of 62.5 kHz
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12);
	// Enable interrupt when reaching the maximum value (OCR1A)
	TIMSK1 = (1 << OCIE1A);
	// Set the timer period to 50 ms (50 * 62.5 = 3125)
	OCR1A = (int) STEP_TIME * 62.5;
	// Reset OC register B and the input capture register. They are not used
	ICR1 = OCR1B = 0;
	// Reset the counter register
	TCNT1 = 0;
	// Enable inerrupts
	interrupts();
}

ISR(TIMER1_COMPA_vect)
{
	static volatile uint8_t step = 0;
	
	for (uint8_t i = 0; i < 4; i++)
	{
		digitalWrite(stepper_pins[i], coil_current[step][i]);
	}
	
	step++;
	if (step >= NUM_STEPS)
	{
		step = 0;
	}
}

void stepper_init(void)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		pinMode(stepper_pins[i], OUTPUT);
	}
	pinMode(EN_PIN, OUTPUT);
	digitalWrite(EN_PIN, HIGH);
}

