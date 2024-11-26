/*
 * File: led_pattern.c
 * Created: [Date]
 * Author: vingyan
 * Description: This program creates a chasing LED pattern on PORTB, where LEDs light up sequentially and then reset.
 * 
 * Detailed Explanation:
 * 1. F_CPU is defined as 16 MHz for delay functions.
 * 2. Pins 8 to 13 of PORTB are set as outputs to control the LEDs.
 * 3. A variable n is initialized to 6.
 * 4. Inside the while loop:
 *    a. A for loop iterates from 0 to n-1.
 *    b. Within the loop, the ith bit of PORTB is set to turn on the corresponding LED.
 *    c. A delay of 200 milliseconds is used to create the chasing effect.
 *    d. The (i-1)th bit of PORTB is cleared to turn off the previous LED.
 *    e. After the loop, n is decremented.
 *    f. If n reaches 0, it is reset to 6, and all LEDs are turned off for a brief period before restarting the pattern.
 */

#define F_CPU 16000000 // Define the clock frequency for delay functions

#include <avr/io.h>     // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

int n = 6; // Initialize variable n with value 6

int main(void) {
    // Set pins 8 to 13 as outputs (PORTB, Pins 0 to 5)
    DDRB |= 0b00111111;

    while (1) { // Infinite loop

        for(int i = 0; i < n; ++i) { // Loop from 0 to n-1
            PORTB |= (1U << i); // Set the ith bit of PORTB to turn on the corresponding pin
            _delay_ms(200); // Delay for 200 milliseconds
            PORTB &= ~(1U << (i - 1)); // Clear the (i-1)th bit of PORTB to turn off the previous pin
        }

        n--; // Decrement n

        if(n == 0) { // If n reaches 0
            n = 6; // Reset n to 6
            _delay_ms(200); // Delay for 200 milliseconds
            PORTB &= ~0b11111111; // Turn off all pins on PORTB
            _delay_ms(200); // Delay for 200 milliseconds
        }
    }

    return 0;
}
