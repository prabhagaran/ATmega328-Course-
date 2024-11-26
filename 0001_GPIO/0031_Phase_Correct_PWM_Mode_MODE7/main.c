/*
 * 0031_Phase_Correct_PWM_Mode_MODE7.c
 *
 * Created: 22-09-2023 11:47:53 AM
 * Author : vingyan
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>


int main()
{
	DDRD |= (1<<PD5);    //Phase Correct PWM output at OC0B pin

	OCR0A = 200;	// Top Value of 200(must be equal or greater than Duty Cycle)
	OCR0B = 102;	// Duty cycle of 40%
	TCCR0A |= (1<<COM0B1) | (1<<WGM00);	//Non-Inverting Fast PWM mode 5
	TCCR0B |= (1<<WGM02) | (1<<CS00);	//No-Prescalar

	while (1);

	return 0;
}
