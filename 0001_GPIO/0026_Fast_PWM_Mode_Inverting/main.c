#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>


int main()
{
	DDRD |= (1<<PD6);    //Fast PWM output at OC0A pin
	
	OCR0A = 63;	// Duty cycle of 75%
	TCCR0A |= (1<<COM0A1) | (1<<COM0A0) | (1<<WGM01) | (1<<WGM00);	//Inverting Fast PWM mode 3
	TCCR0B |= (1<<CS00);	//No-Prescalar

	while (1);

	return 0;
}
