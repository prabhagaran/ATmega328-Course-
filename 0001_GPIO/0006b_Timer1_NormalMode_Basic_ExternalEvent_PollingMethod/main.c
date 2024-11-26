/*
 * File: external_event_counter_polling.c
 * Author: [Author Name]
 * Description: This program demonstrates the use of Timer/Counter 1 as an external event counter using polling.
 * Notes:

		 This program demonstrates the use of Timer/Counter 1 as an external event counter using polling.
		 Timer/Counter 1 is configured in normal mode with a prescaler of 1024, and external events are detected on the rising edge (ICP1 pin).
		 The setup_timer1_normal function initializes Timer/Counter 1 and enables external events on the rising edge.
		 The main loop continuously checks the Input Capture Flag using polling. If an external event is detected, it increments the event count variable and executes the corresponding code.
		 The event count is printed over UART. 
 */ 

#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library
#include "uart.h" // UART Library
#include <avr/interrupt.h> // AVR Interrupt Handling Library

#define F_CPU 16000000 // Define the clock frequency

volatile uint32_t eventCount = 0; // Variable to store the number of external events

void setup_timer1_normal() {
    // Set Timer1 in normal mode with a prescaler of 1024
    TCCR1B = (1 << CS12) | (1 << CS10); // Set prescaler to 1024

    // Enable external events on the rising edge (ICP1 pin)
    TCCR1B |= (1 << ICES1);
}

int main(void) {
    setup_timer1_normal(); // Initialize Timer1
    Serial_begin(9600); // Initialize UART communication
    DDRB &= ~(1 << PB0); // Set PB0 as input
    PORTB |= (1 << PB0); // Enable pull-up resistor for PB0

    while (1) {
        // Your main code goes here
        // Polling method to check Input Capture Flag
        if (TIFR1 & (1 << ICF1)) {
            // Increment the event count variable
            eventCount++;

            // Your code to be executed on each external event goes here

            // Clear the Input Capture Flag
            TIFR1 |= (1 << ICF1);
        }

        SerialPrintf("%d\r\n", eventCount); // Print event count over UART
    }

    return 0;
}
