/*
 * File: timer1_delay_ms.c
 * Author: vingyan
 * Description: This program demonstrates how to create a delay using Timer/Counter 1 in CTC mode.
 * Notes:

		This program demonstrates how to create a delay using Timer/Counter 1 in Clear Timer on Compare (CTC) mode.
		The timer1_delay_ms function sets up Timer/Counter 1 in CTC mode and waits for a specified number of milliseconds.
		Adjust the prescaler and OCR1A value according to your specific requirements and clock frequency.
 */ 

#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // Delay Library

void timer1_delay_ms(uint16_t milliseconds) {
    // Set Timer/Counter1 to CTC (Clear Timer on Compare Match) mode
    TCCR1B |= (1 << WGM12);

    // Calculate the value to load into the OCR1A register
    // Formula: (F_CPU / (prescaler * 1000)) * milliseconds - 1
    // For example, with a 16MHz clock, a prescaler of 64, and 1000ms delay:
    // OCR1A = (16000000 / (64 * 1000)) - 1 = 249
    OCR1A = (F_CPU / 64 / 1000) * milliseconds - 1;

    // Set prescaler to 64 (adjust as needed)
    TCCR1B |= (1 << CS11) | (1 << CS10);

    // Clear the timer register
    TCNT1 = 0;

    // Wait until the OCF1A flag is set (indicating the desired delay has passed)
    while (!(TIFR1 & (1 << OCF1A)));

    // Clear the OCF1A flag by writing a 1 to it
    TIFR1 |= (1 << OCF1A);
}

int main() {
    // Initialize your hardware or set up the microcontroller as needed
    DDRB |= (1 << PB5); // Set PB5 as output

    while (1) {
        // Your main code here

        PORTB ^= (1 << PB5); // Toggle LED on PB5
        timer1_delay_ms(3000); // Delay for 3000 milliseconds (3 seconds)
    }

    return 0;
}
