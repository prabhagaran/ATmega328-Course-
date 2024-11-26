/*
 * 0030_Phase_correct_PWM_Mode_OCR0B.c
 *
 * Created: 22-09-2023 11:38:31 AM
 * Author : vingyan
 */ 

#ifndef F_CPU 
#define F_CPU 16000000
#endif
#include <avr/io.h>
#include <util/delay.h>




int main(void)
{
    DDRD |= (1U << PD5);
	
   TCCR0A |= (1U << COM0B1) | (1U << WGM00);
   TCCR0B |= (1U << CS00);
    while (1) 
    {
		
		for(int i = 0; i <= 255 ; i++)
		{
			OCR0B = i;
			
			_delay_ms(10);
		}
		
    }
}

