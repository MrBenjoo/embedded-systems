/*
 * task_led.h
 *
 * Created: 12/23/2016 1:31:44 PM
 *  Author: Benjamin
 */ 


#ifndef TASK_LED_H_
#define TASK_LED_H_

#define TASK_LED_STACK_SIZE     (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY     (tskIDLE_PRIORITY)
#define LED0_GPIO 13 

void task_led(void *pvParameters);


#endif /* TASK_LED_H_ */