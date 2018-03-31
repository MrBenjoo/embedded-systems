/*
 * adcFunctions.h
 *
 * Created: 2017-11-23 08:59:27
 *  Author: Benjamin Sejdic & George Albert Florea
 */ 


#ifndef ADCFUNCTIONS_H_
#define ADCFUNCTIONS_H_

#define ADC_BASE_ADDRESS 0x400C0000U

#include <inttypes.h>

int analogInit(int pinNumber);
uint32_t analogRead(int pinNumber);

#endif /* ADCFUNCTIONS_H_ */