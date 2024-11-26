/*
 * File: binary_counter.c
 * Created: [Date]
 * Author: vingyan
 * Description: This program implements a simple binary counter using four LEDs connected to pins 8 to 11 of PORTB on an AVR microcontroller.
 * 
 * Detailed Explanation:
 * 1. F_CPU is defined as 16 MHz for delay functions.
 * 2. Pins 8 to 11 of PORTB are set as outputs to control the LEDs.
 * 3. A count variable is initialized to keep track of the binary count.
 * 4. Inside the while loop:
 *    a. The binary count is displayed on the LEDs by setting PORTB to the current value of the count.
 *    b. The count is incremented and wrapped around to 0 after reaching 15 (1111 in binary).
 *    c. A delay of 1000 milliseconds (1 second) is used to control the LED update speed.
 */

#define F_CPU 16000000 // Define the clock frequency for delay functions

#include <avr/io.h>     // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

int main(void) {
    // Set pins 8 to 11 as outputs (PORTB, Pins 0 to 3)
    DDRB |= 0b00001111;

    int count = 0; // Initialize count variable

    while (1) { // Infinite loop
        // Display binary count on LEDs
        PORTB = count;

        // Increment count and loop back to 0 after 15
        count = (count + 1) % 16;

        _delay_ms(1000); // Delay to control LED update speed (1000 milliseconds)
    }

    return 0;
}
