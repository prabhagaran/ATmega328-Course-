/*
 * gpio.c
 *
 * Created: 01-09-2023 01:24:48 PM
 *  Author: vingyan
 */ 

#include "gpio.h"




void pinMode(uint8_t pin, pindirection direction)
{
	
	if(pin < 8)
	{
		if(direction == INPUT)
		{
			DDRD &= ~(1U << pin);
		}
		else if(direction == OUTPUT)
		{
			DDRD |= (1U << pin);
		}
		else if(direction == INPUT_PULLUP)
		{
			
			DDRD &= ~(1U << pin);
			PORTD |= (1U << pin);
		}
		
	}
	else if (pin < 14)
	{
		
		if(direction == INPUT)
		{
			DDRB &= ~(1U << (pin - 8));
		}
		else if(direction == OUTPUT)
		{
			
			DDRB |= (1U << (pin - 8));
		}
		else if(direction == INPUT_PULLUP)
		{
			
			DDRB &= ~(1U << (pin - 8));
			PORTB |= (1U << (pin - 8));
		}
	}
	else if(pin <  20)
	{
		if(direction == INPUT)
		{
			
			DDRC &= ~(1U << (pin - 14));
		}
		else if(direction == OUTPUT)
		{
			
			DDRC |= (1U << (pin - 14));
		}
		else if(direction == INPUT_PULLUP)
		{
			DDRC &= ~(1U << (pin - 14));
			PORTC |= (1U << (pin - 14));
		}
		
	}
	
}

void digitalWrite(uint8_t pin,uint8_t value)
{
	if(pin < 8)
	{
		if(value == 1)
		{
			
			PORTD |= (1U << pin);
		}
		else if(value == 0)
		{
			PORTD &= (1U << pin);
		}
		
	}
	else if(pin < 14)
	{
		if(value == 1)
		{
			
			PORTB |= (1U << (pin - 8));
		}
		else if(value == 0)
		{
			
			PORTB &= ~(1U << (pin - 8));
		}
		
	}
	
	else if(pin < 20)
	{
		
		if(value == 1)
		{
			
			PORTC |= (1U << (pin - 14));
		}
		else if(value == 0)
		{
			PORTC &= ~(1U << (pin - 14));
			
		}
	}
}

uint8_t digitalRead(uint8_t pin)
{
	
	if(pin < 8)
	{
		
		return (PIND & (1U << pin))? 1:0;
	}
	else if(pin < 14)
	{
		return (PINB & (1U << (pin - 8)))? 1:0;
		
	}
	else if(pin < 20)
	{
		
		return (PINC & (1U << (pin - 14)))? 1:0;
	}
	
	return 0;
}