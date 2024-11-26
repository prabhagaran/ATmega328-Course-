/*
 * gpio.h
 *
 * Created: 01-09-2023 01:24:14 PM
 *  Author: vingyan
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#define F_CPU 16000000UL // Define the clock frequency
#include <avr/io.h>
#include <util/delay.h>

#define A0          14
#define A1          15
#define A2          16
#define A3          17
#define A4          18
#define A5          19

#define BUILTIN_LED 13

#define HIGH        1
#define LOW         0
typedef enum
{
	INPUT,
	OUTPUT,
	INPUT_PULLUP
	
	}pindirection;

void pinMode(uint8_t pin, pindirection direction);
void digitalWrite(uint8_t pin,uint8_t value);
uint8_t digitalRead(uint8_t pin);


#endif /* GPIO_H_ */