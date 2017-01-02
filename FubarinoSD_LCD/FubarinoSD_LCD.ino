/*
* FubarinoSD_lcd.ino
*
* Created: 12/31/2016 1:33:20 PM
* Author: nbourg8
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10,9,8,7);

int mainMenu = 0;
int bat_main = 0;
int bat_secondary = 0;
int max_menu_count = 6;
float speed = 0;
int spin = 0;
int vert_angle = 0;
int horiz_angle = 0;

void setup()
{
	lcd.begin(16, 2);		// set up the lcd's number of columns and rows:
	Serial.begin(115200);	// USB Comm Port
	//Serial0.begin(115200);// UART1 - pins 8 (RX) and 9 (TX)
	Serial1.begin(115200);  // UART2 - pins 28 (RX) and 29 (TX)
	lcd.clear();
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
				Serial.print(mySerialData[i], HEX);
				Serial.print(',');
			}
			Serial.println();
		}

		//Detect Button Press
		if (mySerialData[20] == B0001)
		{
			mainMenu++;
		}
		else if (mySerialData[20] == B0010)
		{
			mainMenu--;
		}
		else if (mySerialData[20] == B0100)
		{
			editParam(mainMenu, "left");
		}
		else if (mySerialData[20] == B1000)
		{
			editParam(mainMenu, "right");
		} //end Detect Button Press
		
		// Handle Menu Rollover
		if (mainMenu < 0)
		{
			mainMenu = max_menu_count;
		}
		else if (mainMenu > max_menu_count)
		{
			mainMenu = 0;
		}//End Handle Menu Rollover
		
		//Show proper menu on LCD
		if (mainMenu == 0)
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("%    Bat Main");
			lcd.setCursor(1,0);
			lcd.print(bat_main);
			lcd.setCursor(0,1);
			lcd.print("%    Bat 2nd");
			lcd.setCursor(1,1);
			lcd.print(bat_secondary);
		}
		else if (mainMenu == 1)
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Save Settings?");
			lcd.setCursor(0,1);
			lcd.print("L=No, R=YES");
		}
		else if (mainMenu == 2)
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Factory Reset?");
			lcd.setCursor(0,1);
			lcd.print("L=No, R=YES");
		}
		else if (mainMenu == 3)
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Speed:      MPH");
			lcd.setCursor(0,1);
			lcd.print("0  to 100 MPH");
			lcd.setCursor(7,0);
			lcd.print(speed);
		}
		else if (mainMenu == 4)
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Spin Amt. %");
			lcd.setCursor(0,1);
			lcd.print("(-50% to +50%)");
			lcd.setCursor(11,0);
			lcd.print(spin);
		}
		else if (mainMenu == 5)
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Vert Angle   deg");
			lcd.setCursor(0,1);
			lcd.print("(0 to 90)");
			lcd.setCursor(11,0);
			lcd.print(vert_angle);
		}
		else if (mainMenu == 6)
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Hor. Angle   deg");
			lcd.setCursor(0,1);
			lcd.print("(-30 to +30)");
			lcd.setCursor(11,0);
			lcd.print(horiz_angle);
		}//End Show proper menu on LCD
	}
}

void editParam(int param, String direction)
{
	switch (param)
	{
		case 1: //Save Settings
		//perform save settings
		//print confirmation message for 1 second
		break;
		
		case 2: //Factory Reset
		//perform Factory Reset
		//print confirmation message for 1 second
		break;
		
		case 3: //Speed 0 to 100 MPH
		if (direction == "right" && speed < 255)
		{
			speed = speed + 1;
		}
		if (direction == "left" && speed > 0)
		{
			speed = speed - 1;
		}
		break;
		
		case 4: //Spin Amount -50% to +50%
		if (direction == "right" && spin < 50)
		{
			spin = spin + 1;
		}
		else if (direction == "left" && spin > -50)
		{
			spin = spin - 1;
		}
		break;
		case 5: //Vertical Angle 0 to 90 degrees
		if (direction == "right" && vert_angle < 90)
		{
			vert_angle = vert_angle + 1;
		}
		else if (direction == "left" && vert_angle > 0)
		{
			vert_angle = vert_angle - 1;
		}
		break;
		case 6: //Horiz Angle -30 to +30 degrees
		if (direction == "right" && horiz_angle < 30)
		{
			horiz_angle = horiz_angle + 1;
		}
		else if (direction == "left" && horiz_angle > -30)
		{
			horiz_angle = horiz_angle - 1;
		}
		break;
	}
}