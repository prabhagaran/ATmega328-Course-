/*
 * File: timer_counter_interrupt_LED.c
 * Created: [Date and Time]
 * Author: [Author Name]
 * Description: This program initializes Timer/Counter0 to toggle an LED at regular intervals using interrupts.
 *Notes:
	 This program initializes Timer/Counter0 to toggle an LED at regular intervals using interrupts.
	 The LED pin is defined as PB0.
	 Timer/Counter 0 is configured in Normal mode with a prescaler of 1024.
	 The Timer/Counter 0 Overflow Interrupt is enabled to toggle the LED state.
	 The main loop is left empty as the LED toggling is handled by the interrupt service routine.
 */

#include <avr/io.h> // AVR Standard I/O Library
#include <avr/interrupt.h> // AVR Interrupt Library

// Define the LED pin
#define LED_PIN PB0

// Interrupt Service Routine (ISR) for Timer/Counter 0 overflow
ISR(TIMER0_OVF_vect) {
    // Toggle the LED state
    PORTB ^= (1 << LED_PIN);
}

// Function to initialize Timer/Counter0
void timer0_init() {
    // Set Timer/Counter 0 in Normal mode
    TCCR0A = 0;
    TCCR0B = 0;

    // Set prescaler to 1024
    TCCR0B |= (1 << CS02) | (1 << CS00);

    // Enable Timer/Counter 0 Overflow Interrupt
    TIMSK0 |= (1 << TOIE0);
}

// Function to initialize IO ports
void io_init() {
    // Set the LED pin as an output
    DDRB |= (1 << LED_PIN);
}

int main(void) {
    // Initialize IO ports
    io_init();

    // Initialize Timer/Counter 0
    timer0_init();

    // Enable global interrupts
    sei();

    while (1) {
        // Your main code goes here
        // The LED will toggle at regular intervals due to the interrupt
    }

    return 0;
}
