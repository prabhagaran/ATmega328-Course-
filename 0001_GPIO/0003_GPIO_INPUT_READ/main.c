/*
 * File: switch_led_control.c
 * Created: 30-08-2023 04:08:25 PM
 * Author: vingyan
 * Description: This program controls an LED (connected to PB5) based on the state of a switch (connected to PC0).
 * 
 * Detailed Explanation:
 * 1. F_CPU is defined as 16 MHz for delay functions.
 * 2. PC0 is set as input to read the state of the switch.
 * 3. PB5 is set as output to control the LED.
 * 4. Inside the while loop:
 *    a. If the switch (PC0) is pressed (low), the LED (PB5) is turned on.
 *    b. If the switch (PC0) is not pressed (high), the LED (PB5) is turned off.
 *    c. The loop continuously checks the state of the switch and updates the LED accordingly.
 */

// Define the clock frequency for delay functions
#define F_CPU 16000000

#include <avr/io.h>         // AVR Standard I/O Library
#include <util/delay.h>     // AVR Delay Functions Library

int main(void)
{
    // Setting PC0 as input (switch) and PB5 as output (LED)
    DDRC &= ~(1U << PC0);   // Set PC0 as input
    DDRB |= (1U << PB5);    // Set PB5 as output
	
    while (1) // Infinite loop
    {
        if (!(PINC & (1U << PC0))) // If switch is pressed (PC0 is low)
        {
            PORTB |= (1U << PB5); // Turn on LED (PB5)
        }
        else // If switch is not pressed (PC0 is high)
        {
            PORTB &= ~(1U << PB5); // Turn off LED (PB5)
        }
    }
}
