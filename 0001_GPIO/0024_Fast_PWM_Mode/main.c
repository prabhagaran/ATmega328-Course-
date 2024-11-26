/*
 * 0024_Fast_PWM_Mode.c
 *
 * Created: 21-09-2023 05:03:21 PM
 * Author : vingyan
 */ 


#ifndef F_CPU
#define F_CPU 16000000
#endif
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
    /* Replace with your application code */
	
	DDRD |= (1U << PD6);
	OCR0A = 10;
	TCCR0A |= (1U << COM0A1) | (1U << WGM01) | (1U << WGM00);
	TCCR0B |= (1U << CS00);
    while (1) 
    {
		for(int i =0 ;i <= 255; i++)
		{
			OCR0A = i;
			_delay_ms(10);
			
		}
		
    }
}

