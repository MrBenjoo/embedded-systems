/**
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 *
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <inttypes.h>
#include "task_player1.h"
#include "task_player2.h"
#include "task_control.h"
#include "lcdFunctions.h"
#include "lcdApplication.h"
#include "delayFunctions.h"
#include "adcFunctions.h"
#include "buttons.h"
#include "consoleFunctions.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <stdio_serial.h>


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	/* Init io-port pins */
	sysclk_init();
	board_init();
	ioport_init();
	
	delayInit();
	delayMicroseconds(100000);
	analogInit(0);
	delayMicroseconds(100000);
	lcdInit();
	
	configureConsole();
	delayMicroseconds(100000);

	pmc_enable_periph_clk(ID_TRNG);
	trng_enable(TRNG);
	
	ioport_set_pin_dir(PIO_PB26_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PB26_IDX, HIGH);
	
	printf("Createing tasks...\n");
	xTaskCreate(task_player2, (const signed char * const) "player2", TASK_PLAYER2_STACK_SIZE, NULL, TASK_PLAYER2_PRIORITY, NULL);
	xTaskCreate(task_player1, (const signed char * const) "player1", TASK_PLAYER1_STACK_SIZE, NULL, TASK_PLAYER1_PRIORITY, NULL);                     
	xTaskCreate(task_control, (const signed char * const) "control", TASK_CONTROL_STACK_SIZE, NULL, TASK_CONTROL_PRIORITY, NULL);
	
	xSemaphorePlayer2 = 0;
	xSemaphorePlayer1 = 0;
	
	
	vSemaphoreCreateBinary(xSemaphorePlayer2 );
	vSemaphoreCreateBinary(xSemaphorePlayer1 );
	xSemaphoreTake(xSemaphorePlayer1, 0);
	xSemaphoreTake(xSemaphorePlayer2, 0);
	
	
	/* Start the FreeRTOS scheduler running all tasks indefinitely*/    
	printf("Starting scheduler...\n");
	vTaskStartScheduler();
}
