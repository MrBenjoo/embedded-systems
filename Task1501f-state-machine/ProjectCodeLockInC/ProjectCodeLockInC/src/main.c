/*
* Author: George Albert Florea & Benjamin Sejdic
*
*/
#include <asf.h>
#include "Tasks/task_codeLock.h"
#include "consoleFunctions.h"
#include "Tasks/task_led.h"



int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();

	/* Initialise console UART */
	configureConsole();
	
	printf("-- FreeRTOS Exemple – Tasks --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	
	/* Create the first task for running the code lock */
	if( xTaskCreate(task_codeLock, (const signed char * const) "codeLock", TASK_CODELOCK_STACK_SIZE, NULL, TASK_CODELOCK_STACK_PRIORITY, NULL) != pdPASS )
	{
		printf("Failed to create code lock task\r\n");
	}

	/* Create the second task with blinking LED */
	if( xTaskCreate(task_led, (const signed char * const) "led", TASK_LED_STACK_SIZE, NULL, TASK_LED_STACK_PRIORITY, NULL) != pdPASS ) 
	{
		printf("Failed to create LED task\r\n");
	}

	/* Start the FreeRTOS scheduler running all tasks indefinitely*/
	vTaskStartScheduler();
}
