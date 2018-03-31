/*
* main.c
*
* Created: 12/15/2016 9:22:55 PM
*  Author: Benjamin Sejdic & George Albert Florea
*/

#include "TestButtons.h"
#include "../src/asf.h"
#include "../delayFunctions.h"

int main(void)
{
	/* Initialize the SAM system */
	SystemInit();
	board_init();
	sysclk_init();
	
	pinMode(GREEN_BUTTON, INPUT); /* set green button as an input */
	pinMode(YELLOW_BUTTON, INPUT); /* set yellow button as an input */
	pinMode(RED_BUTTON, INPUT); /* set red button as an input */
	//delayMicroseconds(200);
	
	pinMode(GREEN_LED, OUTPUT); /* set green led as an output */
	pinMode(YELLOW_LED, OUTPUT); /* set yellow led as an output */
	pinMode(RED_LED, OUTPUT); /* set red led as an output */
	pinMode(UNLOCKED_LED, OUTPUT); /* set big led as an output */
	//delayMicroseconds(200);
	
	digitalWrite(GREEN_LED, LOW);
	digitalWrite(YELLOW_BUTTON, LOW);
	digitalWrite(RED_BUTTON, LOW);
	digitalWrite(UNLOCKED_LED, LOW);
	//delayMicroseconds(200);
	while(1)
	{
		if(digitalRead(GREEN_BUTTON) == HIGH)
		{
			//delayMicroseconds(200);
			digitalWrite(GREEN_LED, HIGH);
		}
		else if(digitalRead(YELLOW_BUTTON) == HIGH)
		{
			//delayMicroseconds(200);
			digitalWrite(YELLOW_LED, HIGH);
		}
		else if(digitalRead(RED_BUTTON) == HIGH)
		{
			//delayMicroseconds(200);
			digitalWrite(RED_LED, HIGH);
		}
		//delayMicroseconds(500);
		digitalWrite(GREEN_LED, LOW);
		digitalWrite(YELLOW_BUTTON, LOW);
		digitalWrite(RED_BUTTON, LOW);
	}
}
