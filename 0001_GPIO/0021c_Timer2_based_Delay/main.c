/*
 * File: timer2_delay_ms.c
 * Author: Vingyan
 * Description: This program demonstrates how to create a delay using Timer/Counter 2.
 * Notes:

		 This program demonstrates how to create a delay using Timer/Counter 2.
		 Timer 2 is set up in normal mode with a prescaler of 1024 for a 1ms delay.
		 Adjust the prescaler and the count value according to your specific requirements and clock frequency.
 */ 

#include <avr/io.h> // AVR Standard I/O Library

#define LED PB5 // Define the LED pin

void T2delayOnems(void);
void T2delayms(int n);

int main() {
    DDRB |= (1 << LED); // Set LED pin as output

    while (1) {
        PORTB ^= (1 << LED); // Toggle the LED
        T2delayms(1000); // Delay for 1000 milliseconds (1 second)
    }

    return 0;
}

void T2delayOnems() {
    // Setup Timer 2
    TCNT2 = 248; // Load count value for 1ms time delay
    TCCR2A = 0x00;
    TCCR2B = (1 << CS22) | (1 << CS20); // Normal mode with 1024 prescaler

    while (!(TIFR2 & (1 << TOV2))); // Wait until TOV2 flag is set
    TCCR2B = 0; // Turn off Timer 2
    TIFR2 |= (1 << TOV2); // Clear TOV2 flag
}

void T2delayms(int n) {
    for (int i = 0; i < n; i++) {
        T2delayOnems();
    }
}
