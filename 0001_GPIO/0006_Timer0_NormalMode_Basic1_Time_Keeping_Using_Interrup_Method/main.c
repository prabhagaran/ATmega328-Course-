/*
 * File: elapsed_time_counter.c
 * Created: [Date and Time]
 * Author: vingyan
 * Description: This program initializes Timer/Counter0 of an AVR microcontroller to count elapsed seconds.
 *              It utilizes the prescaler to divide the clock frequency by 1024, generating timer overflows at regular intervals.
 *              Each time the overflow interrupt occurs, the elapsedSeconds variable is incremented, representing the number of seconds that have passed.
 *              The program continuously prints the elapsed time to the serial monitor via UART communication at a baud rate of 9600.
 * 
 * Notes: 
 * 1. Make sure to include the uart.h library for UART communication.
 * 2. Ensure that the baud rate in Serial_begin() matches the baud rate of the serial monitor.
 */

#include <avr/io.h>         // AVR Standard I/O Library
#include <avr/interrupt.h>  // AVR Interrupt Library
#include "uart.h"           // UART Library

volatile uint8_t elapsedSeconds = 0; // Variable to store the elapsed time

// Function to initialize Timer/Counter0
void timer0_init() {
    // Set the prescaler to 1024 (clock divided by 1024)
    TCCR0B |= (1 << CS02) | (1 << CS00);

    // Enable timer overflow interrupt
    TIMSK0 |= (1 << TOIE0);

    // Initialize the counter value (optional)
    TCNT0 = 0;
}

// Timer/Counter0 overflow interrupt handler
ISR(TIMER0_OVF_vect) {
    // Increment the elapsed time
    elapsedSeconds++;
}

int main() {
    // Initialize Timer/Counter0
    timer0_init();
    
    // Initialize serial communication at 9600 baud rate
    Serial_begin(9600);

    // Enable global interrupts
    sei();

    while (1) {
        // Display the elapsed time to the serial monitor
        SerialPrintf("ElapsedSecond = %d\n\r", elapsedSeconds);
    }

    return 0;
}
