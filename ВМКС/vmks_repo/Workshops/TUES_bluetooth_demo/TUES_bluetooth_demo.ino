/*
	TUES Bluetooth Demo - an example for controlling motors over Bluetooth
	Copyright (C) 2023 Vladimir Garistov <vgaristov@elsys-bg.org>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Affero General Public License as published
	by the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

// Board selection. Comment out for Arduino AVR boards.
#define _ESP32_

// Dabble configuration options
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#define INCLUDE_GAMEPAD_MODULE
#ifdef _ESP32_
	// Does not compile with increased warnings in Arduino IDE because some are treated as errors.
	#include <DabbleESP32.h>
	#include <ESP32Servo.h>
#else
	#include <Dabble.h>
	#include <Servo.h>
#endif

#ifdef _ESP32_
	#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BT_BLUEDROID_ENABLED)
		#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
	#endif
	#if !defined(CONFIG_BT_SPP_ENABLED)
		#error Serial Port Profile for Bluetooth is not available or not enabled.
	#endif

	#define LED_PIN		2
	#define SERVO_PIN	22
	#define MOTOR_A_PIN	19
	#define MOTOR_B_PIN	21
#else
	#define LED_PIN		13
	#define SERVO_PIN	10
	#define MOTOR_A_PIN	11
	#define MOTOR_B_PIN	12
	#define RX_PIN		2
	#define TX_PIN		3
	#define BT_BAUDRATE	9600
#endif

#define UART_BAUDRATE	38400
#define UART_TIMEOUT	10		// ms

static void serial_relay(void);
static void joystick_execute(void);

#ifdef _ESP32_
	static const char device_name[] = "ESP32-BT-Slave";
#endif

static Servo servo_1;

void setup()
{
	#ifdef _ESP32_
		Dabble.begin(device_name);
	#else
		Dabble.begin(BT_BAUDRATE, RX_PIN, TX_PIN);
	#endif

	pinMode(LED_PIN, OUTPUT);
	pinMode(MOTOR_A_PIN, OUTPUT);
	pinMode(MOTOR_B_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
	digitalWrite(MOTOR_A_PIN, LOW);
	digitalWrite(MOTOR_B_PIN, LOW);

	servo_1.attach(SERVO_PIN);

	Serial.begin(UART_BAUDRATE);
	Serial.setTimeout(UART_TIMEOUT);
	Serial.println("Setup complete.");
}

void loop()
{
	// This function is used to refresh data obtained from smartphone.
	// Hence calling this function is mandatory in order to get data properly from your mobile.
	Dabble.processInput();
	serial_relay();
	joystick_execute();
	delay(50);
}

/*
	Relays data from the Bluetooth module to the UART interface and vice-versa.
	A maximum of 256 characters can be sent from the UART interface to the Bluetooth module.
	Otherwise the buffer of the Serial library fills up and characters are silently dropped.
	A maximum of 64 characters can be sent from the Bluetooth module to the UART interface.
	In this case the buffer of the Dabble library fills up. Result is the same - some
	characters are silently dropped.
	Does not work correctly for non-ASCII characters.
	Tested on Arduino Uno and ESP32, the lenght limits might differ on other boards.
*/
static void serial_relay(void)
{
	static String serial_data = "";
	static bool data_flag = false;

	if (Serial.available())
	{
		// Blocks for UART_TIMEOUT
		serial_data = Serial.readString();
		data_flag = true;
	}
	if (data_flag == true)
	{
		Terminal.print(serial_data);
		serial_data = "";
		data_flag = false;
	}
	if (Terminal.available())
	{
		while (Terminal.available())
		{
			Serial.write(Terminal.read());
		}
		Serial.println();
	}
}

static void joystick_execute(void)
{
	static uint8_t servo_pos = 0;
	static bool led_on = false;
	bool motor_forward = true;
	uint8_t motor_speed = 0;
	float angle_y = 0.0;

	if (GamePad.isStartPressed())
	{
		led_on = !led_on;
		digitalWrite(LED_PIN, led_on);
	}
	if (GamePad.isSquarePressed() && servo_pos > 0)
	{
		servo_pos--;
		servo_1.write(servo_pos);
	}
	if (GamePad.isCirclePressed() && servo_pos < 180)
	{
		servo_pos++;
		servo_1.write(servo_pos);
	}
	angle_y = GamePad.getYaxisData();
	motor_forward = angle_y > 0.0 ? true : false;
	motor_speed = (uint8_t) (abs(angle_y) * 36.0);
	if (motor_forward)
	{
		digitalWrite(MOTOR_B_PIN, LOW);
		analogWrite(MOTOR_A_PIN, motor_speed);
	}
	else
	{
		digitalWrite(MOTOR_A_PIN, LOW);
		analogWrite(MOTOR_B_PIN, motor_speed);
	}
}