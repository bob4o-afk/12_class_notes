#include <Wire.h>

#define POT_PIN	A0
#define LED_PIN	10

#define SLAVE_ADDRESS	0x09

void i2c_receive_handler(int bytes_received);
void i2c_send_handler(void);

volatile bool led_status = false;
volatile uint16_t pot_value = 0;

void setup()
{
	pinMode(POT_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	Wire.begin(SLAVE_ADDRESS);
	Wire.onRequest(i2c_send_handler);
	Wire.onReceive(i2c_receive_handler);

	Serial.begin(9600);
}

void loop()
{
	digitalWrite(LED_PIN, led_status);
	pot_value = analogRead(POT_PIN);
}

void i2c_send_handler(void)
{	
	//Only for demonstration, never actually put Serial.print() in an ISR
	Serial.print("Sending pot_value = ");
	Serial.println(pot_value);
	Wire.write((uint8_t *) &pot_value, sizeof(pot_value));
}

void i2c_receive_handler(int bytes_received)
{
	led_status = Wire.read();
	// Ignore all bytes but the first
	for (int i = 1; i < bytes_received; i++)
	{
		Wire.read();
	}
	//Only for demonstration, never actually put Serial.print() in an ISR
	Serial.println(led_status ? "LED on": "LED off");
}
