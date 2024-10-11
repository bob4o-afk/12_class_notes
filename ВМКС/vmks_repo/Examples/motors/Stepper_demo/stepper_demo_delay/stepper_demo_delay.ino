#include <inttypes.h>

#define A1_PIN	9
#define A2_PIN	8
#define B1_PIN	11
#define B2_PIN	10
#define EN_PIN	12

#define STEP_TIME 1000  // ms

//#define FULL_STEP
#define HALF_STEP

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

const uint8_t stepper_pins[4] = {A2_PIN, A1_PIN, B1_PIN, B2_PIN};

void setup()
{
	for (uint8_t i = 0; i < 4; i++)
	{
		pinMode(stepper_pins[i], OUTPUT);
	}
	pinMode(EN_PIN, OUTPUT);
	digitalWrite(EN_PIN, HIGH);
}

void loop()
{
	static uint8_t step = 0;
	
	for (uint8_t i = 0; i < 4; i++)
	{
		digitalWrite(stepper_pins[i], coil_current[step][i]);
	}
	
	step++;
	if (step >= NUM_STEPS)
	{
		step = 0;
	}
	
	delay(STEP_TIME);
}
