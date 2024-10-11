/*
  LiquidCrystal Library - scrollDisplayLeft() and scrollDisplayRight()

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and uses the
 scrollDisplayLeft() and scrollDisplayRight() methods to scroll
 the text.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi
 modified 24 Feb 2021
 by Vladimir Garistov

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalScroll

*/

#include <LiquidCrystal.h>

#define RS	12
#define EN	11
#define D4	5
#define D5	4
#define D6	3
#define D7	2

#define COLS 16
#define ROWS 2

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup()
{
	delay(40); // LCD Power-On Reset (POR) initialization wait
	// set up the LCD's number of columns and rows:
	lcd.begin(COLS, ROWS);
	lcd.print("hello, world!");
	delay(1000);
}

void loop()
{
	// scroll 13 positions (string length) to the left
	// to move it offscreen left:
	for (uint8_t positionCounter = 0; positionCounter < 13; positionCounter++)
	{
		// scroll one position left:
		lcd.scrollDisplayLeft();
		delay(150);
	}

	// scroll 29 positions (string length + display length) to the right
	// to move it offscreen right:
	for (uint8_t positionCounter = 0; positionCounter < 29; positionCounter++)
	{
		// scroll one position right:
		lcd.scrollDisplayRight();
		delay(150);
	}

	// scroll 16 positions (display length + string length) to the left
	// to move it back to center:
	for (uint8_t positionCounter = 0; positionCounter < 16; positionCounter++)
	{
		// scroll one position left:
		lcd.scrollDisplayLeft();
		delay(150);
	}

	delay(1000);
}
