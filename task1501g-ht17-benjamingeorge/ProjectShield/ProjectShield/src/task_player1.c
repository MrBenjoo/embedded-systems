/*
 * task_player1.c
 *
 * Created: 2018-02-01 11:25:38
 *  Author: George Albert Florea
 *	Author: Benjamin Sejdic
 */ 

#include <asf.h>
#include "task_player1.h"
#include "lcdFunctions.h"
#include "lcdApplication.h"
#include "buttons.h"
#include "task_control.h"
#include "semphr.h"


void task_player1(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 1000/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();
	
	//task_player1
	while(1) {
		vTaskDelayUntil( &xLastWakeTime, xTimeIncrement );
		printf("task_player1\n");
		//väntar på att spelare ska trycka på btnUP på LCD'n
		while(readLCDbutton() != btnUP) 
		{
			
		}
		xSemaphoreGive(xSemaphorePlayer1);
	}
		
	/*portTickType xLastWakeTime;
	portTickType xTimeIncrement = 10/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
		printf("task_player1\n");
		while(readLCDbutton() != btnUP)
		{
			//vTaskDelay(10/portTICK_RATE_MS);
		}
		xSemaphoreGive(xSemaphorePlayer1); // Öka semaforen till 1
		printf("task_player1 END\n");
	
		//vTaskDelay(10/portTICK_RATE_MS);
	}*/
}
