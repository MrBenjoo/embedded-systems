/*
* stateMachine.c
*
* Created: 12/14/2016 11:10:34
*  Author: George Albert Florea & Benjamin Sejdic
*/

#include "stateMachine.h"

codeLockType SM;			/* The memory area for the state machine */
codeLockPtrType instance;	/* A pointer to a state machine of this type */

/*
* The assignment of the pointer to the memory area for the state machine,
* instance = &SM, is done in test_FSM_runner.c
*/


const states OurTransitionTable[NO_OF_STATES][NO_OF_EVENTS] = {
	/* This is the full logic of the state machine */
	{ PushOne, Locked,  Locked, Locked},
	{ PushOne, Locked,  Locked, ReleaseOne},
	{ Locked, Locked,  PushTwo, ReleaseOne},
	{ Locked, Locked,  PushTwo, ReleaseTwo},
	{ Locked, Locked,  PushThree, ReleaseTwo},
	{ Locked, Locked,  PushThree, ReleaseThree},
	{ Locked, PushFour,  Locked, ReleaseThree},
	{ Locked, PushFour,  Locked, OPEN},
	{ Locked, Locked,  Locked, OPEN}
};

void startCodeLock(codeLockPtrType foo)     /* Making sure the FSM starts in the right state */
{
	foo->state = Locked;
}

void pushButton1(codeLockPtrType foo)		/* Yellow button is pushed */
{
	const states currentState = foo->state;
	foo->state = OurTransitionTable[currentState][yellowButton];
}

void pushButton2(codeLockPtrType foo)		/* Red button is pushed */
{
	const states currentState = foo->state;
	foo->state = OurTransitionTable[currentState][redButton];
}

void pushButton3(codeLockPtrType foo)		/* Green button is pushed */
{
	const states currentState = foo->state;
	foo->state = OurTransitionTable[currentState][greenButton];
}


void releaseButton(codeLockPtrType foo)	    /* No button is pushed */
{
	const states currentState = foo->state;
	foo->state = OurTransitionTable[currentState][releaseBtn];
}


