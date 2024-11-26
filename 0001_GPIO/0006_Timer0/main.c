/*
 * File: 0021_8bit_timer_normal_mode_interrupt.c
 * Created: 20-09-2023 03:49:30 PM
 * Author: vingyan
 * Description: This program toggles an LED connected to PB5 (Arduino pin 13) using Timer0 in normal mode.
 *              The LED is toggled approximately every 204.8 milliseconds using a polling method for the Timer0 overflow flag.
 * 
 * Timer Configuration:
 * - Prescaler: 64
 * - Timer0 clock: F_CPU / 64 = 16 MHz / 64 = 250 kHz
 * - Timer0 overflow frequency: 250 kHz / 256 ? 976.5625 Hz
 * - Number of overflows to toggle LED: 200
 * - Toggle interval: 200 / 976.5625 Hz ? 0.2048 seconds (204.8 ms)
 * 
 * Detailed Explanation:
 * 1. The program configures PB5 as an output pin for the LED.
 * 2. Timer0 is configured in normal mode with a prescaler of 64.
 * 3. The main loop continuously polls the Timer0 Overflow Flag (TOV0).
 * 4. Each time an overflow occurs, the overflow counter (elapsedtime) is incremented.
 * 5. When the overflow counter reaches 200, the LED is toggled and the counter is reset.
 * 6. This results in the LED toggling approximately every 204.8 milliseconds.
 */

#include <avr/io.h> // Include AVR IO definitions

// Global variable to keep track of elapsed time in terms of Timer0 overflows
uint16_t elapsedtime = 0;

int main() {
    // Set Pin 13 (PB5) as output
    DDRB |= (1 << DDB5);

    // Configure Timer0 in normal mode (WGM01 and WGM00 are cleared by default)
    TCCR0A = 0;

    // Set prescaler to 64 for Timer0 (Timer0 clock = F_CPU / 64)
    TCCR0B |= (1 << CS01) | (1 << CS00);

    while (1) {
        // Poll the Timer0 Overflow Flag (TOV0)
        if (TIFR0 & (1 << TOV0)) {
            elapsedtime++; // Increment elapsed time counter
            // Clear the Timer0 Overflow Flag by writing a 1 to it
            TIFR0 |= (1 << TOV0);
        }

        // Check if 200 Timer0 overflows have occurred
        if (elapsedtime == 200) {
            PORTB ^= (1 << PB5); // Toggle the LED connected to PB5
            elapsedtime = 0; // Reset the elapsed time counter
        }
    }

    return 0; // This line will never be reached
}
