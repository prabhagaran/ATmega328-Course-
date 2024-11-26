/*
 * File: timer_delay.c
 * Author: vingyan
 * Description: This program demonstrates the use of Timer/Counter 1 for creating delays.
 * Notes:

		 This program demonstrates the use of Timer/Counter 1 for creating delays.
		 Timer/Counter 1 is configured in normal mode with a prescaler of 1024.
		 The delay_ms function calculates the number of timer ticks needed for the given milliseconds and waits until the timer overflows the required number of times to achieve the delay.
		 An LED connected to PB5 is toggled at regular intervals to visualize the delay.
 */ 

#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

#define F_CPU 16000000 // Define the clock frequency

void setup_timer1() {
    // Set Timer1 in normal mode with a prescaler of 1024
    TCCR1B = (1 << CS12) | (1 << CS10); // Set prescaler to 1024
}

void delay_ms(uint16_t milliseconds) {
    // Calculate the number of timer ticks needed for the given milliseconds
    uint16_t ticks = (uint16_t)((float)milliseconds * (F_CPU / 1000.0) / 1024.0);

    // Set the initial timer value
    TCNT1 = 0;

    // Wait until the timer overflows the required number of times
    while (TCNT1 < ticks) {}

    // Reset the timer value for the next delay
    TCNT1 = 0;
}

int main(void) {
    setup_timer1(); // Initialize Timer1
    DDRB |= (1 << PB5); // Set PB5 as output

    while (1) {
        // Your main code goes here
        PORTB ^= (1 << PB5); // Toggle PB5

        // Example: Delay for 1000 milliseconds (1 second)
        delay_ms(1000);
    }

    return 0;
}
