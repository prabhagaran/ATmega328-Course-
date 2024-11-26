/*
 * 0028_Fast_PWM_Mode_MODE7.c
 *
 * Created: 21-09-2023 05:58:37 PM
 * Author : vingyan
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>


int main()
{
	DDRD |= (1<<PD5);    //Fast PWM output at OC0B pin
	
	OCR0A = 200;	// Top Value of 200(must be equal or greater than Duty Cycle)
	OCR0B = 191;
	TCCR0A |= (1<<COM0B1) | (1<<COM0B0) | (1<<WGM01) | (1<<WGM00);	//Inverting Fast PWM mode 3
	TCCR0B |= (1<<CS00);	//No-Prescalar

	while (1);

	return 0;
}

