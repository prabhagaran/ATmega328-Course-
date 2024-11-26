/*
 * 0037_Input_Capture_Frequency_Measuement.c
 *
 * Created: 11-10-2023 12:13:20 PM
 * Author : vingyan
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"


int main(void)
{
	Serial_begin(9600);
	unsigned int a,b,c,high,period;
    DDRD |=   (1U << PB0);
	PORTD &= ~(1U << PB0);
	
	
	
    while (1) 
    {
		TCCR1A = 0;
		TCNT1 = 0;
		TIFR1 = (1U << ICF1);
		
		TCCR1B  = 0x41; 
		while((TIFR1 & (1U << ICF1)) == 0){}
		a = ICR1;
		TIFR1 = (1U << ICF1);
		
		TCCR1B  = 0x01;
		while((TIFR1 & (1U << ICF1)) == 0){}
		b = ICR1;
		TIFR1 = (1U << ICF1);
		
		TCCR1B  = 0x41;
		while((TIFR1 & (1U << ICF1)) == 0){}
		c = ICR1;
		TIFR1 = (1U << ICF1);
		
		TCCR1B = 0;
		
		if((a < b) && (b < c))	
		{
			high = b-a;
			period = c-a;
			
			double freq = ((double)F_CPU / (double)period) / 1000;
			float duty_cycle = ((float)high / (float)period) * 100;
			
			SerialPrintf("The Frequency : %0.2f KHz Dutycyle : %0.2f%% \r\n",freq,duty_cycle);
		}
			
    }
}

