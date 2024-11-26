/*
 * File: 0022_CTC_MODE_USING_POLLING.c
 * Description: AVR code for generating a square wave using CTC mode with polling
 * Created: 21-09-2023 01:02:59 PM
 * Author: vingyan
 */ 

#define F_CPU 16000000 // Define CPU frequency for delay calculation
#include <avr/io.h>    // AVR Input/Output macros

// Function to set up CTC mode for generating square wave
void CTC_MODE(void)
{
	// Set the value for output compare register for desired frequency
	OCR0A = 249; // For 1kHz square wave at 16MHz clock
	
	// Configure Timer/Counter Control Registers for CTC mode and toggle OC0A on compare match
	TCCR0A |= (1 << COM0A0) | (1 << WGM01);
	// Set prescaler to 8
	TCCR0B |= (1 << CS01);
	
	// Poll until the output compare flag is set
	while(!(TIFR0 & (1 << OCF0A))) {}
	// Clear the output compare flag
	TIFR0 = (1 << OCF0A);
}

int main(void)
{
    /* Replace with your application code */
	// Set PD6 as output pin for generating square wave
	DDRD |= (1 << PD6);
    
    while (1) 
    {
		// Call CTC_MODE function to generate square wave
		CTC_MODE();
    }
}
