/*
 * 0011_GPIO_DRIVERS_LED_BLINK.c
 *
 * Created: 01-09-2023 01:21:57 PM
 * Author : vingyan
 */ 

#define F_CPU 16000000UL // Define the clock frequency
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"


int main(void)
{
    /* Replace with your application code */
	pinMode(BUILTIN_LED,OUTPUT);
	
    while (1) 
    {
	
	digitalWrite(BUILTIN_LED,HIGH);
	_delay_ms(500);
	digitalWrite(BUILTIN_LED,LOW);
	_delay_ms(500);
		
		
    }
}

