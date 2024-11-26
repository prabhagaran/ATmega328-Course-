/*
 * File: 0023_Timer0_CTC_Mode_Interrupt.c
 * Description: AVR code for generating a square wave using Timer0 in CTC mode with interrupt
 * Created: 21-09-2023 03:24:37 PM
 * Author: vingyan
 */ 

#ifndef F_CPU
#define F_CPU 16000000 // Define CPU frequency if not defined
#endif
#include <avr/io.h>      // AVR Input/Output macros
#include <avr/interrupt.h>// AVR interrupt handling

int main(void)
{
    /* Replace with your application code */
	DDRD |= (1U << PD6); // Set PD6 as output pin
    
	// Configure OCR0A register for desired frequency
	OCR0A = 7; // Example value for generating a specific frequency
	
	// Configure Timer/Counter Control Registers for CTC mode and toggle OC0A on compare match
	TCCR0A |= (1U << COM0A0) | (1U << WGM01);
	// Set prescaler to 1024
	TCCR0B |= (1U << CS02) | (1U << CS00);
	// Enable Timer0 Output Compare A Match Interrupt
	TIMSK0 |= (1U << OCIE0A);
	
	// Enable global interrupts
	sei();
	
    while (1) 
    {
		// Main program loop
    }
}

// Timer0 Output Compare A Match Interrupt Service Routine
ISR(TIMER0_COMPA_vect)
{
	// Interrupt service routine code here
	// This ISR will be executed each time Timer0 reaches the value in OCR0A
	// You can add your desired functionality here, such as toggling pins, etc.
}
