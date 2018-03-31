/*
* task_player2.c
*
* Created: 2018-02-01 11:28:43
*  Author: George Albert Florea
*	Author: Benjamin Sejdic
*/

#include <asf.h>
#include "task_player2.h"
#include "lcdFunctions.h"
#include "lcdApplication.h"
#include "buttons.h"
#include "task_control.h"
#include "semphr.h"


void task_player2(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 1000/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();
	
	//task_player2
	while(1) {
		vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
		printf("task_player2\n");
		//väntar på att spelare ska trycka på btnUP på LCD'n
		while(readLCDbutton() != btnDOWN) 
		{
		}
		xSemaphoreGive(xSemaphorePlayer2);
	}
}