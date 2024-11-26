/*
 * File: 0006b_Timer1_NormalMode_Basic.c
 * Author: VINGYAN 
 * Description: This program demonstrates the basic usage of Timer/Counter 1 in normal mode.
 *              It configures Timer/Counter 1 to run in normal mode with a prescaler of 64.
 *              The program continuously reads the timer counter value and toggles an LED on PB5.
 * Notes:

	 This program demonstrates the basic usage of Timer/Counter 1 in normal mode with a prescaler of 64.
	 Timer/Counter 1 is configured to continuously count and overflow at regular intervals.
	 The program reads the timer counter value and sends it over serial communication for monitoring.
	 An LED connected to PB5 is toggled each time Timer/Counter 1 overflows, providing a visual indication of the timer operation.
 */ 

#include <avr/io.h> // AVR Standard I/O Library
#include "uart.h" // UART Library for serial communication

uint32_t timerCounterValue; // Variable to store the timer counter value

int main(void) {
    Serial_begin(9600); // Initialize serial communication at 9600 baud rate
    
    // Configure Timer/Counter 1 in normal mode with a prescaler of 64
    TCCR1A = 0; // Clear Timer/Counter 1 Control Register A
    TCCR1B |= (1 << CS11) | (1 << CS10); // Set prescaler to 64
    
    TCNT1 = 0; // Initialize the counter value
    
    DDRB |= (1 << PB5); // Set PB5 as output for LED
    
    while (1) {
        // Read the timer counter value
        timerCounterValue = TCNT1;
        
        // Send the timer counter value over serial communication
        SerialPrintf("Timer Counter Value = %lu\n\r", timerCounterValue);
        
        // Wait until Timer/Counter 1 overflows
        while (!(TIFR1 & (1 << TOV1))) {
            // Your main code goes here
        }

        // Timer/Counter 1 has overflowed
        TIFR1 |= (1 << TOV1); // Clear the overflow flag
        
        // Toggle the LED on PB5
        PORTB ^= (1 << PB5);
    }
    
    return 0;
}

