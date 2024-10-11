/* 
 * ASCII => Char
 *  0x56 => V
 *  0x0A => [LINE FEED]
 *  0x0D => [CARRIAGE RETURN]
 */

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Serial.print('V');		// Sends 0x56
//	Serial.println('V');	// Sends 0x56 0x0D 0x0A
//	Serial.write(0x56);		// Sends 0x56

	while(Serial.available() > 0)
	{
		Serial.read();
	}
	delay(500);
}
