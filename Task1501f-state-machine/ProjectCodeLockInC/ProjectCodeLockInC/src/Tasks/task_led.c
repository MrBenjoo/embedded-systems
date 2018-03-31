/*
 * task_led.c
 *
 * Created: 12/23/2016 1:31:07 PM
 *  Author: Benjamin Sejdic & George Albert Florea
 */ 

#include "task_led.h"
#include "../asf.h"

/**
 *  This tasks makes the on-board LED blink every second
 */
void task_led(void *pvParameters)
{
    portTickType xLastWakeTime;
    const portTickType xTimeIncrement = 500;

    xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
    while (1) {
        vTaskDelayUntil(&xLastWakeTime, xTimeIncrement); /* Wait for the next cycle. */
        gpio_toggle_pin(LED0_GPIO);
    }
}