/*
* Task1.c
*
* Created: 12/20/2016 4:33:20 PM
*  Author: Benjamin Sejdic & George Albert Florea
*/


#include "../asf.h"
#include "../Statemachine/stateMachine.h"
#include "../TestButtons/TestButtons.h"
#include "../consoleFunctions.h"
#include "../delayFunctions.h"


/**
* This task will run the code lock and change the I/O
*/
void task_codeLock(void *pvParameters)

{
	/* ------------------------ Init pins ----------------------- */
	pinMode(GREEN_BUTTON, INPUT);  /* set green button as an input */
	pinMode(YELLOW_BUTTON, INPUT); /* set yellow button as an input */
	pinMode(RED_BUTTON, INPUT);    /* set red button as an input */

	pinMode(GREEN_LED, OUTPUT);    /* set green led as an output */
	pinMode(YELLOW_LED, OUTPUT);   /* set yellow led as an output */
	pinMode(RED_LED, OUTPUT);      /* set red led as an output */
	pinMode(UNLOCKED_LED, OUTPUT); /* set big led as an output */

	digitalWrite(GREEN_LED, LOW);
	digitalWrite(YELLOW_LED, LOW);
	digitalWrite(RED_LED, LOW);
	digitalWrite(UNLOCKED_LED, HIGH);
	/* --------------------------------------------------------- */
	
	/* Initialise console UART */
	configureConsole();
	
	delayInit();
	
	codeLockType SM;
	codeLockPtrType instance;
	
	instance = &SM; /* Points to the memory area of codelock */
	startCodeLock(instance); /* Making the statemachine start in locked state */
	
	while(1)
	{

		if(digitalRead(YELLOW_BUTTON) == HIGH)
		{
			while(digitalRead(YELLOW_BUTTON) == HIGH)
			{
				pushButton1(instance);
				delayMicroseconds(500000); /* This delay is needed to give the program a chance to turn off the LEDs in the locked state, otherwise it goes from locked state to pushOne almost instantaneously */
			}

			releaseButton(instance);
		}
		
		else if(digitalRead(GREEN_BUTTON) == HIGH)
		{
			while(digitalRead(GREEN_BUTTON) == HIGH)
			{
				pushButton3(instance);
			}
			
			releaseButton(instance);
		}
		
		else if(digitalRead(RED_BUTTON) == HIGH)
		{
			while(digitalRead(RED_BUTTON) == HIGH)
			{
				pushButton2(instance);
			}
			
			releaseButton(instance);
		}
		
		/* ---------- Controlling the code lock lamps ---------- 
		* lamps[0] = YELLOW_LED
		* lamps[1] = GREEN_LED
		* lamps[2] = RED_LED
		* lamps[3] = UNLOCKED_LED 
		*/
		if(instance->state == Locked)
		{
			instance->lamps[0] = LOW;
			instance->lamps[1] = LOW;
			instance->lamps[2] = LOW;
			instance->lamps[3] = HIGH;
			digitalWrite( YELLOW_LED, instance->lamps[0] );
			digitalWrite( GREEN_LED, instance->lamps[1] );
			digitalWrite( RED_LED, instance->lamps[2] );
			digitalWrite( UNLOCKED_LED, instance->lamps[3] );
		}
		else if(instance->state == ReleaseOne)
		{
			instance->lamps[0] = HIGH;
			digitalWrite( YELLOW_LED, instance->lamps[0] );
		}
		else if(instance->state == ReleaseTwo)
		{
			instance->lamps[1] = HIGH;
			digitalWrite( GREEN_LED, instance->lamps[1] );
		}
		else if(instance->state == ReleaseThree)
		{
			instance->lamps[2] = HIGH;
			digitalWrite( RED_LED, instance->lamps[2] );
		}
		else if(instance->state == OPEN)
		{
			instance->lamps[3] = LOW;
			digitalWrite( UNLOCKED_LED, instance->lamps[3] );
		}
		/*----------------------------------------------------*/
		
		vTaskDelay(200); /* 200 millisecond delay */
	}

}

