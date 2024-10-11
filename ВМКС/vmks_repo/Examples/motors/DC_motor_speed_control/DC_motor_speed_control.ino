#define DRV_IN1	11
#define DRV_IN2	10
#define DRV_EN	12
#define POT		A0

void setup()
{
	pinMode(DRV_IN1, OUTPUT);
	pinMode(DRV_IN2, OUTPUT);
	pinMode(DRV_EN, OUTPUT);
	pinMode(POT, INPUT);
	digitalWrite(DRV_IN1, LOW);
	digitalWrite(DRV_IN2, LOW);
	digitalWrite(DRV_EN, HIGH);
}

void loop()
{
	// Instead of /4, map() or >>2 can be used.
	analogWrite(DRV_IN1, analogRead(POT) / 4);
}
