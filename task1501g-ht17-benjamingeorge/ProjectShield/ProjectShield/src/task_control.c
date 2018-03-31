/*
* task_control.c
*
* Created: 2018-02-01 11:25:38
*  Author: George Albert Florea
*  Author: Benjamin Sejdic
*/

#include <asf.h>
#include "task_control.h"
#include "lcdApplication.h"
#include "buttons.h"
#include "lcdFunctions.h"
#include "FreeRTOS.h"

#define xBlockTime 100
portTickType xTimeStampTicks;
portTickType timeStart;
uint32_t reactionTimePlayer1;
uint32_t reactionTimePlayer2;
bool player1btnPressed = false;
bool player2btnPressed = false;

void task_control(void *pvParamters)
{
	portTickType xLastWakeTime;
	portTickType xTimeIncrement = 6000/portTICK_RATE_MS;
	xLastWakeTime = xTaskGetTickCount();
	bool gameStarted = false;
	
	//task_control
	while(1)
	{
		printf("task_control\n");
		while(!gameStarted)
		{
			lcdWrite(0b00000001, LOW); /* Clear display */
			if(readLCDbutton() == btnSELECT){
				gameStarted = true;
				printf("lcdWriteAsciiString(...)\n");
				lcdWriteAsciiString("Game started");
				vTaskDelay(1000);
				
				uint32_t randomNumberMillis = (getRandomNumber()*1000);
				ioport_set_pin_level(PIO_PB26_IDX, LOW);
				
				lcdWrite(0b00000001, LOW); // Clear display 
				printf("RANDOM_NUMBER_MILLIS: %d\n", randomNumberMillis);
				
				vTaskDelay(randomNumberMillis/portTICK_RATE_MS);
				
				timeStart = xTaskGetTickCount();
				printf("TIME_START: %d\n", timeStart);
				ioport_set_pin_level(PIO_PB26_IDX, HIGH);
			}
		}
		
		// Räkna ut reaktionstiden för Player 1
		if(xSemaphoreTake(xSemaphorePlayer1, 0) == pdTRUE) {
			printf("xSemaphorePlayer1\n");
			player1btnPressed = true;
			reactionTimePlayer1 = (int)(xTaskGetTickCount() - timeStart)/portTICK_RATE_MS;
			if(reactionTimePlayer1<50){
				lcdWriteAsciiString("Player 1 cheated");
				vTaskDelay(2000/portTICK_RATE_MS);
				lcdWrite(0b00000001, LOW); // Clear display
				vTaskDelay(1000/portTICK_RATE_MS);
				lcdWriteAsciiString("GAME OVER");
				while(1);
			}
			printf("Player1 reaction time: %d\n", reactionTimePlayer1 );
		}
		
		// Räkna ut reaktionstiden för Player 1
		if(xSemaphoreTake(xSemaphorePlayer2, 0) == pdTRUE) {
			printf("xSemaphorePlayer2\n");
			player2btnPressed = true;
			reactionTimePlayer2 = (int)(xTaskGetTickCount() - timeStart)/portTICK_RATE_MS;
			printf("Player2 reaction time: %d\n", reactionTimePlayer2 );
			if(reactionTimePlayer2<50){
				lcdWriteAsciiString("Player 2 cheated");
				vTaskDelay(2000/portTICK_RATE_MS);
				lcdWrite(0b00000001, LOW); // Clear display
				vTaskDelay(1000/portTICK_RATE_MS);
				lcdWriteAsciiString("GAME OVER");
				while(1);
			}
		}
		
		//Gränstiden på 2 sekunder har passerat
		if(!player2btnPressed || !player1btnPressed){
			if ( (int)(xTaskGetTickCount()-timeStart)/portTICK_RATE_MS > 2000) {
				printf("xTastGetTickCount: %d\n", xTaskGetTickCount());
				printf("2 SECOND LIMIT PASSED, GAME OVER\n");
				lcdWriteAsciiString("2 second limit");
				vTaskDelay(1000/portTICK_RATE_MS);
				lcdWrite(0b00000001, LOW); // Clear display
				vTaskDelay(1000/portTICK_RATE_MS);
				lcdWriteAsciiString("Game over");
				while(1){
					//DO NOTHING
				}
			}
		}
		
		//Spelare 1 och 2 har trckt på sina knappar minst en gång efter spelet startats
		if(player1btnPressed && player2btnPressed){
			if(reactionTimePlayer1<reactionTimePlayer2){
				printf("player1");
				lcdWriteAsciiString("Player1 has won!");
				
				vTaskDelay(1000/portTICK_RATE_MS);
				lcdWrite(0b00000001, LOW); // Clear display 
				vTaskDelay(1000/portTICK_RATE_MS);
				
				lcdWriteAsciiString("Player1 reaction:");
				lcdWrite(0x80 | (1 << 6) | 0, LOW);
				lcdWrite4DigitNumber(reactionTimePlayer1);
				lcdWriteAsciiString(" ms");
				
				vTaskDelay(1000/portTICK_RATE_MS);
				lcdWrite(0b00000001, LOW); // Clear display 
				vTaskDelay(1000/portTICK_RATE_MS);
				
				lcdWriteAsciiString("Player2 reaction: ");
				lcdWrite(0x80 | (1 << 6) | 0, LOW);
				lcdWrite4DigitNumber(reactionTimePlayer2);
				lcdWriteAsciiString(" ms");
				vTaskDelay(100/portTICK_RATE_MS);
				
				} else{
				printf("player2");
				lcdWriteAsciiString("Player2 has won!");
				
				vTaskDelay(1000/portTICK_RATE_MS);
				lcdWrite(0b00000001, LOW); // Clear display
				vTaskDelay(1000/portTICK_RATE_MS);
				
				lcdWriteAsciiString("Player2 reaction:");
				lcdWrite(0x80 | (1 << 6) | 0, LOW);
				lcdWrite4DigitNumber(reactionTimePlayer2);
				lcdWriteAsciiString(" ms");
				
				vTaskDelay(1000/portTICK_RATE_MS);
				lcdWrite(0b00000001, LOW); // Clear display
				vTaskDelay(1000/portTICK_RATE_MS);
				
				lcdWriteAsciiString("Player1 reaction: ");
				lcdWrite(0x80 | (1 << 6) | 0, LOW);
				lcdWrite4DigitNumber(reactionTimePlayer1);
				lcdWriteAsciiString(" ms");
				vTaskDelay(100/portTICK_RATE_MS);
				
			} 
			while(1)
			{
			}
			
		}
		
		printf("%s --- Player1btnPressed ---\n", player1btnPressed ? "true" : "false");
		printf("%s --- Player2btnPressed ---\n", player2btnPressed ? "true" : "false");
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}


uint8_t getRandomNumber(){
	uint32_t nbr = trng_read_output_data(TRNG);  //Läs 32-bitars slumptal
	uint8_t interval = (nbr >> 29) ;
	if((interval & (0b00000111))+2>7)
	interval = (interval & (0b00000101))+2;
	else
	interval = (interval & (0b00000111))+2;
	return interval;
}