/**
 * @file main.c
 *
 * @brief main file initiating all necessary hardware and then blinking LED
 *
 * @author Benjamin Sejdic & George Albert Florea
 *
 * @date 2015-12-17
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "DigitalIO/digitalIO.h"/* Functions developed in Task1501a */
#include "DelayFunctions.h"
#include "WatchDog/WTDTimer.h"
#include "DAC/initDAC.h"
#include "TimerCounter/TimerCounter.h"
#include "consoleFunctions.h"

#define CONF_BOARD_KEEP_WATCHDOG_AT_INIT 1		//to keep watchdog activated at board_init

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	sysclk_init();
	board_init();
	
	configureConsole();
	
	// Delay initialization
	delayInit();
	
	// DAC initialization
	daccInit();

	// Insert application code here, after the board has been initialized.
	init_timer();
	
	/* Init io-port pins */
	ioport_init();
	ioport_set_pin_dir(PIO_PB26_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);
	
	
	while(1)	/* repeat blink to infinity */
	{
		//watchdogReload();
		ioport_set_pin_level(PIO_PB27_IDX, HIGH);
		ioport_set_pin_level(PIO_PB27_IDX, LOW);
		//digitalWrite(13, 1); /* sets a bit of I/O port B to high */
		//printf("1");
		//delayMicroseconds(500000);
		//digitalWrite(13, 0); /* clears a bit of I/O port B */
		// printf("0");
		//delayMicroseconds(500000);
	}
}
