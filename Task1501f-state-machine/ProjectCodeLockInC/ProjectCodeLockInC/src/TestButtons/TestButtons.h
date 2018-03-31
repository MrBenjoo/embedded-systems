/*
* IncFile1.h
*
* Created: 12/15/2016 7:59:07 PM
*  Author: Benjamin Sejdic & George Albert Florea
*/


#ifndef INCFILE1_H_
#define INCFILE1_H_

/* LED */
#define UNLOCKED_LED 9 /* Connected to digital PIN 9 (PC21) */
#define RED_LED 8      /* Connected to digital PIN 8 (PC22) */
#define YELLOW_LED 7   /* Connected to digital PIN 7 (PC23) */
#define GREEN_LED 6    /* Connected to digital PIN 6 (PC24) */

/* BUTTONS */
#define GREEN_BUTTON 3  /* Connected to digital PIN 3 (PC28) */
#define YELLOW_BUTTON 4 /* Connected to digital PIN 4 (PC26) */
#define RED_BUTTON 5    /* Connected to digital PIN 5 (PC25) */

typedef enum {
	OUTPUT,
	INPUT
} mode_definition;

void pinMode(int pinNumber, mode_definition mode);
void digitalWrite(int pinNumber, int value);
int digitalRead(int pinNumber);

#endif /* INCFILE1_H_ */