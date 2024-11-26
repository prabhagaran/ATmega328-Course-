/*
 * 0032_Phase_Correct_PWM_Inverting_Mode_OCR0A.c
 *
 * Created: 22-09-2023 11:54:12 AM
 * Author : vingyan
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>


int main()
{
	DDRD |= (1<<PD6);    //Phase Correct PWM output at OC0A pin
	
	OCR0A = 153;	// Duty cycle of 40%
	TCCR0A |= (1<<COM0A1) | (1<<COM0A0) | (1<<WGM00);	//Inverting Phase Correct PWM mode 1
	TCCR0B |= (1<<CS00);	//No-Prescalar

	while (1);

	return 0;
}
