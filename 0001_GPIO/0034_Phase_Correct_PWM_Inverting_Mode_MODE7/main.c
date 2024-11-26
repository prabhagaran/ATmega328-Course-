/*
 * 0034_Phase_Correct_PWM_Inverting_Mode_MODE7.c
 *
 * Created: 22-09-2023 12:14:35 PM
 * Author : vingyan
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>


int main()
{
	DDRD |= (1<<PD5);    //Phase Correct PWM output at OC0A pin
	OCR0A = 200;	// Top Value of 200(must be equal or greater than Duty Cycle)
	OCR0B = 153;	// Duty cycle of 40%
	
	TCCR0A |= (1<<COM0B1) | (1<<COM0B0) | (1<<WGM00);	//Inverting Phase Correct PWM mode 5
	TCCR0B |= (1<<WGM02) | (1<<CS00);	//No-Prescalar

	while (1);

	return 0;
}