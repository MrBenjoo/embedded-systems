/*
 * Test1.h
 *
 * Created: 12/20/2016 4:34:41 PM
 *  Author: Benjamin
 */ 


#ifndef TEST1_H_
#define TEST1_H_

#define TASK_CODELOCK_STACK_SIZE        (2048/sizeof(portSTACK_TYPE))
#define TASK_CODELOCK_STACK_PRIORITY    (2)

void task_codeLock(void *pvParameters);

#endif /* TEST1_H_ */