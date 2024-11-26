/*
 * File: timer_delay_LED.c
 * Created: [Date and Time]
 * Author: [Author Name]
 * Description: This program toggles an LED using timer delay functions.
 Notes:
	 This program toggles an LED connected to pin PB5 using timer delay functions.
	 Timer0 is utilized to generate delays.
	 The LED pin is defined as PB5.
	 Timer0 is configured in normal mode with a prescaler of 1024 to generate a 1 ms delay.
	 The T0delayms function creates a delay of 'n' milliseconds by calling T0delayOnems 'n' times.
	 The LED is toggled with a delay of 1 second (1000 ms) in the main loop.
 
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h> // AVR Standard I/O Library

#define LED PB5 // Define the LED pin

void T0delayOnems(void); // Function to create a delay of 1 ms using Timer0
void T0delayms(int n); // Function to create a delay of 'n' milliseconds using Timer0

int main() {
    DDRB |= (1 << LED); // Set the LED pin as an output

    while (1) {
        PORTB ^= (1 << LED); // Toggle the LED state
        T0delayms(1000); // Delay for 1000 ms (1 second)
    }
    return 0;
}

// Function to create a delay of 1 ms using Timer0
void T0delayOnems() {
    // Setup Timer 0
    TCNT0 = 248; // Load count value for 1 ms time delay
    TCCR0A = 0x00;
    TCCR0B |= (1 << CS02) | (1 << CS00); // Normal mode with 1024 pre-scaler

    while (!(TIFR0 & (1 << TOV0))); // Wait until TOV0 flag is set
    TCCR0B = 0; // Turn off Timer 0
    TIFR0 |= (1 << TOV0); // Clear TOV0 flag
}

// Function to create a delay of 'n' milliseconds using Timer0
void T0delayms(int n) {
    for (int i = 0; i < n; i++) {
        T0delayOnems();
    }
}
