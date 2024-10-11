#include <Servo.h>

#define DRV_A1		6
#define DRV_A2		5
#define EN_L		7
#define DRV_A3		9
#define DRV_A4		11
#define EN_R		4
#define SERVO_PIN	10

Servo aservo;

void forward(uint8_t speed);
void reverse(uint8_t speed);
void turn_left(uint8_t speed);
void turn_right(uint8_t speed);

void setup()
{
	pinMode(DRV_A1, OUTPUT);
	pinMode(DRV_A2, OUTPUT);
	pinMode(EN_L, OUTPUT);
	digitalWrite(DRV_A1, LOW);
	digitalWrite(DRV_A2, LOW);
	digitalWrite(EN_L, HIGH);
	
	pinMode(DRV_A3, OUTPUT);
	pinMode(DRV_A4, OUTPUT);
	pinMode(EN_R, OUTPUT);
	digitalWrite(DRV_A3, LOW);
	digitalWrite(DRV_A4, LOW);
	digitalWrite(EN_R, HIGH);

	aservo.attach(SERVO_PIN);
}

void loop()
{
	/*
	digitalWrite(DRV_A1, HIGH);
	analogWrite(DRV_A2, 128);
	digitalWrite(EN_L, HIGH);
	*/

	aservo.write(90);

	for (uint8_t i = 0; i < 4; i++)
	{
		forward(255);
		delay(5000);
		turn_right(128);
		delay(1000);
	}
	digitalWrite(EN_L, LOW);
	digitalWrite(EN_R, LOW);
}

void forward(uint8_t speed)
{
	analogWrite(DRV_A1, speed);
	digitalWrite(DRV_A2, LOW);
	analogWrite(DRV_A3, speed);
	digitalWrite(DRV_A4, LOW);
}

void reverse(uint8_t speed)
{
	digitalWrite(DRV_A1, LOW);
	analogWrite(DRV_A2, speed);
	digitalWrite(DRV_A3, LOW);
	analogWrite(DRV_A4, speed);
}

void turn_left(uint8_t speed)
{
	digitalWrite(DRV_A1, LOW);
	analogWrite(DRV_A2, speed);
	analogWrite(DRV_A3, speed);
	digitalWrite(DRV_A4, LOW);
}

void turn_right(uint8_t speed)
{
	analogWrite(DRV_A1, speed);
	digitalWrite(DRV_A2, LOW);
	digitalWrite(DRV_A3, LOW);
	analogWrite(DRV_A4, speed);
}

void stop_motors()
{
	digitalWrite(DRV_A1, LOW);
	digitalWrite(DRV_A2, LOW);
	digitalWrite(DRV_A3, LOW);
	digitalWrite(DRV_A4, LOW);
}
