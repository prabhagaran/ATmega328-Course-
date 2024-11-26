/*
 * File: gpio_toggle.c
 * Created: 30-08-2023 11:40:18 AM
 * Author: vingyan
 * Description: This program toggles the state of pin PB5 of PORTB at regular intervals to blink an LED.
 * 
 * Detailed Explanation:
 * 1. F_CPU is defined as 16 MHz for delay functions.
 * 2. PB5 of PORTB is set as an output to control the LED.
 * 3. Inside the while loop:
 *    a. The state of pin PB5 is toggled using bitwise XOR operation to blink the LED.
 *    b. A delay of 500 milliseconds is applied using _delay_ms() function.
 * 4. This process repeats indefinitely, blinking the LED on and off.
 */

#define F_CPU 16000000 // Define the clock frequency for delay functions

#include <avr/io.h>     // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

int main(void)
{
    // Set pin PB5 of PORTB as output
    DDRB |= (1U << PB5); // configure as OUTPUT
	
    while (1) // Infinite loop
    {
        // Toggle the state of pin PB5 to blink the LED
        PORTB ^= (1U << PB5);
		
        // Delay for 500 milliseconds
        _delay_ms(500);
    }
}
