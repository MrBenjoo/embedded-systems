/*
* TestButtons.c
*
* Created: 12/15/2016 7:58:29 PM
*  Author: Benjamin Sejdic & George Albert Florea
*/

#include <inttypes.h>
//#include "sam.h"
#include <asf.h> /* Only needed to get the definitions for HIGH and LOW */
#include "TestButtons.h"

#define PIOC_BASE_ADDRESS 0x400E1200U /* Start address for PIOC register */

/* REGISTER DEFINITIONS */
uint32_t *const p_PIOC_OER = (uint32_t *) (PIOC_BASE_ADDRESS+0x0010U);	/* defines the address for enabling the parallel output C register */
uint32_t *const p_PIOC_ODR = (uint32_t *) (PIOC_BASE_ADDRESS+0x0014U);  /* defines the address for disabling the parallel output C register */
uint32_t *const p_PIOC_PER = (uint32_t *) (PIOC_BASE_ADDRESS+0x0000U);	/* defines the address for enabling the parallel Input/output C register */
uint32_t *const p_PIOC_SODR = (uint32_t *) (PIOC_BASE_ADDRESS+0x0030U);	/* defines the address for status (values) of the output pins of the C register set to HIGH  */
uint32_t *const p_PIOC_CODR = (uint32_t *) (PIOC_BASE_ADDRESS+0x0034U); /* defines the address for status (values) of the output pins of the C register set to LOW   */
uint32_t *const p_PIOC_PDSR = (uint32_t *) (PIOC_BASE_ADDRESS+0x003CU); /* defines the address for pin data status register, with this register we can read the pins */


void pinMode(int pinNumber, mode_definition mode)
{
	if(mode == OUTPUT)
	{
		if(pinNumber == UNLOCKED_LED)
		{
			*p_PIOC_PER |= (1<<21); /* Enable the PIO to control UNLOCKED_LED */
			*p_PIOC_OER |= (1<<21); /* Set UNLOCKED_LED as an output */
			*p_PIOC_PER ^= (1<<21);	/* Disable the PIO to control UNLOCKED_LED */
		}
		else if(pinNumber == YELLOW_LED)
		{
			*p_PIOC_PER |= (1<<23);
			*p_PIOC_OER |= (1<<23);
			*p_PIOC_PER ^= (1<<23);
		}
		else if(pinNumber == GREEN_LED)
		{
			*p_PIOC_PER |= (1<<24);
			*p_PIOC_OER |= (1<<24);
			*p_PIOC_PER ^= (1<<24);
		}
		else if(pinNumber == RED_LED)
		{
			*p_PIOC_PER |= (1<<22);
			*p_PIOC_OER |= (1<<22);
			*p_PIOC_PER ^= (1<<22);
		}
	}
	else if(mode == INPUT)
	{
		if(pinNumber == GREEN_BUTTON)
		{
			*p_PIOC_PER |= (1<<28); /* Enable the PIO to control GREEN_BUTTON */
			*p_PIOC_ODR |= (1<<28); /* Set GREEN_BUTTON as an input */
			*p_PIOC_PER ^= (1<<28);	/* Disable the PIO to control GREEN_BUTTON */
		}
		else if(pinNumber == YELLOW_BUTTON)
		{
			*p_PIOC_PER |= (1<<26);
			*p_PIOC_ODR |= (1<<26);
			*p_PIOC_PER ^= (1<<26);
		}
		else if(pinNumber == RED_BUTTON)
		{
			*p_PIOC_PER |= (1<<25);
			*p_PIOC_ODR |= (1<<25);
			*p_PIOC_PER ^= (1<<25);
		}
	}
}

void digitalWrite(int pinNumber, int value)
{
	if(value == HIGH)
	{
		if(pinNumber == UNLOCKED_LED)
		{
			*p_PIOC_PER |= (1<<21);  /* Enable the PIO to control UNLOCKED_LED */
			*p_PIOC_SODR |= (1<<21); /* Set UNLOCKED_LED to high */
			*p_PIOC_PER ^= (1<<21);  /* Disable the PIO to control UNLOCKED_LED */
		}
		
		else if(pinNumber == YELLOW_LED)
		{
			*p_PIOC_PER |= (1<<23);
			*p_PIOC_SODR |= (1<<23);
			*p_PIOC_PER ^= (1<<23);
		}
		else if(pinNumber == GREEN_LED)
		{
			*p_PIOC_PER |= (1<<24);
			*p_PIOC_SODR |= (1<<24);
			*p_PIOC_PER ^= (1<<24);
		}
		else if(pinNumber == RED_LED)
		{
			*p_PIOC_PER |= (1<<22);
			*p_PIOC_SODR |= (1<<22);
			*p_PIOC_PER ^= (1<<22);
		}
	}
	else if(value == LOW)
	{
		if(pinNumber == UNLOCKED_LED)
		{
			*p_PIOC_PER |= (1<<21);  /* Enable the PIO to control UNLOCKED_LED */
			*p_PIOC_CODR |= (1<<21); /* Set UNLOCKED_LED to LOW */
			*p_PIOC_PER ^= (1<<21);  /* Disable the PIO to control UNLOCKED_LED */
		}
		else if(pinNumber == YELLOW_LED)
		{
			*p_PIOC_PER |= (1<<23);
			*p_PIOC_CODR |= (1<<23);
			*p_PIOC_PER ^= (1<<23);
		}
		else if(pinNumber == GREEN_LED)
		{
			*p_PIOC_PER |= (1<<24);
			*p_PIOC_CODR |= (1<<24);
			*p_PIOC_PER ^= (1<<24);
		}
		else if(pinNumber == RED_LED)
		{
			*p_PIOC_PER |= (1<<22);
			*p_PIOC_CODR |= (1<<22);
			*p_PIOC_PER ^= (1<<22);
		}
	}
}

int digitalRead(int pinNumber)
{
	if(pinNumber == GREEN_BUTTON)
	{
		int greenBtnPressed = (*p_PIOC_PDSR) & (1<<28); //read GREEN_BUTTON to check if its pressed
		
		if(greenBtnPressed) // if pressed
		{
			return 1;
		}
	}
	else if(pinNumber == YELLOW_BUTTON)
	{
		int yellowBtnPressed = (*p_PIOC_PDSR) & (1<<26);
		
		if(yellowBtnPressed)
		{
			return 1;
		}
	}
	else if(pinNumber == RED_BUTTON)
	{
		int redBtnPressed = (*p_PIOC_PDSR) & (1<<25);
		
		if(redBtnPressed)
		{
			return 1;
		}
	}
	
	return 0;
	
}



