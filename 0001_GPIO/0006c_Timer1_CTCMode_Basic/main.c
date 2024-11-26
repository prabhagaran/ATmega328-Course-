/*
 * File: timer1_ctc_mode_basic.c
 * Author: vingyan
 * Description: This program demonstrates the basic usage of Timer/Counter 1 in CTC mode.
 * Notes:

	 This program demonstrates the basic usage of Timer/Counter 1 in Clear Timer on Compare (CTC) mode.
	 Timer/Counter 1 is configured in CTC mode with a prescaler of 64.
	 The LED connected to pin PB5 is toggled when the Timer1 compare match flag is set.
	 The main function initializes Timer/Counter 1, UART communication, and sets up the LED pin as an output.
	 The program continuously monitors Timer1 and toggles the LED based on the compare match flag.
 */ 

#include <avr/io.h> // AVR Standard I/O Library
#include "uart.h" // UART Library

#define LED_PIN PB5 // LED connected to pin PB5
uint32_t timerCounter;

void setup_timer1_ctc() {
    // Set Timer1 in CTC mode with a prescaler of 64
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

    // Set the compare value for a specific frequency (toggle rate)
    OCR1A = 5000; // Adjust this value for your specific requirements
}

int main(void) {
    setup_timer1_ctc();
    Serial_begin(9600); // Initialize UART communication

    // Set LED pin as an output
    DDRB |= (1 << LED_PIN);

    while (1) {
        timerCounter = TCNT1;
        SerialPrintf("%d\r\n",timerCounter);

        // Polling method to check Timer1 compare match flag
        if (TIFR1 & (1 << OCF1A)) {
            // Toggle the LED
            PORTB ^= (1 << LED_PIN);

            // Clear the Timer1 compare match flag
            TIFR1 |= (1 << OCF1A);
        }

        // Your main code goes here
    }

    return 0;
}
