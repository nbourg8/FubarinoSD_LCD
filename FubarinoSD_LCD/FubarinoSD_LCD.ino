/*
* FubarinoSD_LCD.ino
*
* Created: 12/31/2016 1:33:20 PM
* Author: nbourg8
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10,9,8,7);

void setup()
{
	lcd.begin(16, 2);		// set up the LCD's number of columns and rows:
	Serial.begin(115200);	// USB Comm Port
	//Serial0.begin(115200);// UART1 - pins 8 (RX) and 9 (TX)	
	Serial1.begin(115200);  // UART2 - pins 28 (RX) and 29 (TX)
}
void loop()
{
	int mySerialData[24];

	if (Serial1.available() >=23)	//ensure Serial communication is functional - don't waste time if remote is sleeping
	{
		if (Serial1.read() == 0x7E)	//look for remote address start byte
		{
			for (int i = 1; i<22; i++)	//gather all bytes for later processing
			{
				mySerialData[i] = Serial1.read();
				//Serial.print(mySerialData[i], HEX);
				//Serial.print(',');
			}
			//Serial.println();
		}
		
		//Output to LCD status of remote button
		if (mySerialData[20] >> 2)
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Button Pressed!");
		}
		else
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Button Not Pressed....");
		}
	}
}