/*
 * File: external_event_counter.c
 Author: vingyan
 * Description: This program demonstrates the use of Timer/Counter 1 as an external event counter.
 * Notes:

		 This program demonstrates the use of Timer/Counter 1 as an external event counter.
		 Timer/Counter 1 is configured in normal mode with a prescaler of 1024 and external events are detected on the rising edge.
		 The setup_timer1 function initializes Timer/Counter 1 and enables external events and the Input Capture Interrupt.
		 The main loop continuously prints the event count over UART.
		 The Input Capture Interrupt Service Routine (TIMER1_CAPT_vect) increments the event count variable on each external event.
 */ 

#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library
#include "uart.h" // UART Library
#include <avr/interrupt.h> // AVR Interrupt Handling Library

#define F_CPU 16000000 // Define the clock frequency

volatile uint32_t eventCount = 0; // Variable to store the number of external events

void setup_timer1() {
    // Set Timer1 in normal mode with a prescaler of 1024
    TCCR1B = (1 << CS12) | (1 << CS10); // Set prescaler to 1024

    // Enable external events on the rising edge
    TCCR1B |= (1 << ICES1);

    // Enable Input Capture Interrupt
    TIMSK1 |= (1 << ICIE1);

    // Enable global interrupts
    sei();
}

int main(void) {
    setup_timer1(); // Initialize Timer1
    Serial_begin(9600); // Initialize UART communication
    DDRB &= ~(1 << PB0); // Set PB0 as input
    PORTB |= (1 << PB0); // Enable pull-up resistor for PB0

    while (1) {
        // Your main code goes here
        SerialPrintf("%d\r\n", eventCount); // Print event count over UART
    }

    return 0;
}

// Input Capture Interrupt Service Routine
ISR(TIMER1_CAPT_vect) {
    // Increment the event count variable
    eventCount++;

    // Your code to be executed on each external event goes here
}
