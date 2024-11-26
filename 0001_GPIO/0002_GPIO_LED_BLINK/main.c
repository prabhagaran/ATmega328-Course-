/*
 * File: led_blink.c
 * Created: 30-08-2023 01:19:51 PM
 * Author: vingyan
 * AIM: To blink LED on PORTB PB5
 * Description: This program blinks an LED connected to pin PB5 of PORTB on an AVR microcontroller.
 * 
 * Detailed Explanation:
 * 1. F_CPU is defined as 16 MHz for delay functions.
 * 2. PB5 of PORTB is set as an output to control the LED.
 * 3. Inside the while loop:
 *    a. The LED connected to PB5 is turned on by setting the corresponding bit in PORTB.
 *    b. A delay of 100 milliseconds is applied using _delay_ms() function.
 *    c. The LED connected to PB5 is turned off by clearing the corresponding bit in PORTB.
 *    d. Another delay of 100 milliseconds is applied.
 * 4. This process repeats indefinitely, creating a blinking effect.
 */

// Define the clock frequency for delay functions
#define F_CPU 16000000

#include <avr/io.h>         // AVR Standard I/O Library
#include <util/delay.h>     // AVR Delay Functions Library

int main(void)
{
    // Set pin PB5 of port B as output
    DDRB |= (1U << PB5);

    while (1) // Infinite loop
    {
        // Turn on the LED connected to PB5
        PORTB |= (1U << PB5);
        
        // Delay for 100 milliseconds
        _delay_ms(100);
        
        // Turn off the LED connected to PB5
        PORTB &= ~(1U << PB5);
        
        // Delay for 100 milliseconds
        _delay_ms(100);
    }
}
