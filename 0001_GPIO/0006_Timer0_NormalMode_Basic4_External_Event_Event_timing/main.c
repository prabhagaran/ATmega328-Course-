/*
 * File: timer_counter_interrupt.c
 * Created: [Date and Time]
 * Author: [Author Name]
 * Description: This program initializes Timer/Counter0 in counter mode with interrupt.
 *              It counts pulses using an external event and triggers an interrupt on timer overflow.
 * Note: Adjust the value of YOUR_TIME_THRESHOLD according to the desired time interval for event timing.
 *       The count value is printed over serial communication for monitoring.
 */

#define F_CPU 16000000 // Define the clock frequency for delay functions

#include <avr/io.h> // AVR Standard I/O Library
#include <avr/interrupt.h> // AVR Interrupt Library
#include <util/delay.h> // AVR Delay Functions Library
#include "uart.h" // UART Library

volatile uint16_t timer_count = 0; // Variable to store the count of pulses
uint16_t YOUR_TIME_THRESHOLD = 2000; // Define the time threshold for event timing

// Function to initialize Timer/Counter0 in counter mode with interrupt
void timer0_counter_interrupt_init() {
    // Configure Timer/Counter0 in counter mode with external events (falling edge)
    TCCR0A = 0; // Clear WGM00, WGM01 (normal mode)
    TCCR0B = (1 << CS02)|(1 << CS00); // Set CS02, CS01, CS00 for external events (falling edge)

    // Enable Timer/Counter0 overflow interrupt
    TIMSK0 |= (1 << TOIE0);
}

// Timer/Counter0 overflow interrupt handler
ISR(TIMER0_OVF_vect) {
    // Increment the pulse count
    timer_count++;
}

int main() {
    // Initialize Timer0 in counter mode with interrupt
    timer0_counter_interrupt_init();
    Serial_begin(9600); // Initialize serial communication
    // Enable global interrupts
    sei();

    while (1) {
        // Check the timer_count value for event timing
        if (timer_count >= YOUR_TIME_THRESHOLD) {
            // Event has occurred, perform necessary actions
            // Reset the timer_count for the next event
            timer_count = 0;
        }

        SerialPrintf("The Count Value = %d\r\n", timer_count); // Print count value over serial
    }

    return 0;
}
