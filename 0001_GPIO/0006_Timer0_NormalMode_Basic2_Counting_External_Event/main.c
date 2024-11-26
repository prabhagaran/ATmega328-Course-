/*
 * File: timer_counter_mode.c
 * Created: [Date and Time]
 * Author: [Author Name]
 * Description: This program initializes Timer/Counter0 of an AVR microcontroller in counter mode.
 *              It configures Timer/Counter0 to count external events (falling edges) on T0/PD4 pin.
 *              The count value is read and printed to the serial monitor continuously at a baud rate of 9600.
 * 
 * Notes:
 * 1. Make sure to include the uart.h library for UART communication.
 * 2. Ensure that the baud rate in Serial_begin() matches the baud rate of the serial monitor.
 */

#define F_CPU 16000000  // Define the clock frequency for delay functions

#include <avr/io.h>     // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library
#include "uart.h"       // UART Library

int main() {
    Serial_begin(9600); // Initialize serial communication at 9600 baud rate

    // Initialize Timer0 in counter mode
    // Configure Timer/Counter0 in counter mode (falling edge)
    TCCR0A = 0;                         // Clear WGM00, WGM01 (normal mode)
    TCCR0B = (1 << CS02) | (1 << CS01); // Set CS00 and CS02 for clock source (1024)

    // Set the external event pin (T0/PD4) as an input
    DDRD &= ~(1 << PD4);
    PORTD |= (1 << PD4); // Enable internal pull-up resistor

    uint8_t countValue;

    while (1) {
        // Read the count value from Timer0
        countValue = TCNT0;

        // Print the count value to the serial monitor
        SerialPrintf("The Count Value = %d\r\n", countValue);

        // Delay for a short period (adjust as needed)
        _delay_ms(500);
    }

    return 0;
}
