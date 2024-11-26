/*
 * 0029_Phase_Correct_PWM_Mode_OCR0A.c
 *
 * Created: 22-09-2023 10:31:54 AM
 * Author : vingyan
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>




int main(void)
{
   
    
	DDRD |= (1U << PD6);
	
	TCCR0A |= (1U << COM0A1) | (1U << WGM00);
	TCCR0B |= (1U << CS00);
	
    while (1) 
    {
		for(int i = 0; i <= 255; i++)
		{
			
			OCR0A = i;
			
			_delay_ms(100);
		}
			
    }
}

