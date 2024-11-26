/*
 * File: timer1_normal_mode_basic_interrupt.c
 * Author: VINGYAN 
 * Description: This program demonstrates the basic usage of Timer/Counter 1 in normal mode with interrupt.
 * Notes:
		 This program demonstrates the basic usage of Timer/Counter 1 in normal mode with interrupt.
		 Timer/Counter 1 is configured with a prescaler of 1024.
		 When Timer/Counter1 overflows, the overflow interrupt service routine (ISR) toggles the state of PB5.
		 The main function initializes Timer/Counter 1 and enables its overflow interrupt.
		 The TIMER1_OVF_vect ISR toggles PB5 on Timer/Counter1 overflow.
 */ 

#include <avr/io.h> // AVR Standard I/O Library
#include <avr/interrupt.h> // AVR Interrupt Handling Library

int main(void) {
    DDRB |= (1 << PB5); // Set PB5 as output
    TCCR1A = 0; // Clear Timer/Counter1 Control Register A
    TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
    TIMSK1 |= (1 << TOIE1); // Enable Timer/Counter1 overflow interrupt
    sei(); // Enable global interrupts

    while (1) {
        // Your main code goes here
    }
}

ISR(TIMER1_OVF_vect) {
    // Toggle PB5 on Timer/Counter1 overflow
    PORTB ^= (1 << PB5);
}
