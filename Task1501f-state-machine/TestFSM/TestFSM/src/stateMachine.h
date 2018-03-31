/*
 * stateMachine.h
 *
 * Created: 2015-06-17 14:58:02
 *  Author: Ulrik
 */ 


#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_


typedef enum
{
	Locked,
	PushOne, ReleaseOne,
	PushTwo, ReleaseTwo,
	PushThree, ReleaseThree,
	PushFour,
	OPEN
} states;
#define NO_OF_STATES 9


typedef struct codeLock
{
	states state;	/* Let a variable hold the state of our object. */
	int lamps[4];	/* For the lamps */
} codeLockType;


typedef enum
{
	yellowButton, redButton, greenButton,  releaseBtn 
} Event;
#define NO_OF_EVENTS 4



typedef codeLockType *codeLockPtrType;


void startCodeLock(codeLockPtrType foo);	/* Starting the code lock state machine */
void pushButton1(codeLockPtrType foo);		/* Yellow button is pushed */
void pushButton2(codeLockPtrType foo);		/* Red button is pushed */	
void pushButton3(codeLockPtrType foo);		/* Green button is pushed */
void releaseButton(codeLockPtrType foo);	/* No button is pushed */

#endif /* STATEMACHINE_H_ */