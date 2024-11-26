/*
 * File: timer_led_toggle.c
 * Description: This program toggles an LED connected to pin PB5 using Timer0 interrupts.
 *              It initializes Timer0 in CTC mode with a prescaler, sets up the LED pin as output,
 *              and toggles the LED at a regular interval determined by Timer0 compare match interrupts.
 *              The Timer0 is configured to generate interrupts approximately every 1 millisecond.
 *              The counter value of Timer0 is printed over UART for monitoring purposes.
 * Author: [Your Name]
 
 Notes:
	 This program toggles an LED connected to pin PB5 using Timer0 interrupts.
	 It initializes Timer0 in CTC (Clear Timer on Compare Match) mode with a prescaler to generate interrupts approximately every 1 millisecond.
	 The LED pin (PB5) is configured as an output.
	 The Timer0 compare match interrupt is used to toggle the LED at a regular interval.
	 The counter value of Timer0 is printed over UART for monitoring purposes.

 */

#include "uart.h" // Include UART library header file
#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

uint16_t timercounter = 0; // Variable to store the timer counter value

// Function to initialize Timer0 in CTC mode with prescaler
void timer0_init() {
    TCCR0A |= (1 << WGM01); // Set WGM01 bit to enable CTC mode
    OCR0A = 156; // Set the value for compare match (for 1 ms delay at 16 MHz)
    TCCR0B |= (1 << CS02); // Set prescaler to 256 (adjust as needed)
}

// Function to wait for the Timer0 compare match
void wait_for_timer0_match(int n) {
    for(int i = 0; i <= n; i++) {
        while (!(TIFR0 & (1 << OCF0A))) {
            // Wait until the Timer0 compare match flag is set
        }
        TIFR0 |= (1 << OCF0A); // Clear the Timer0 compare match flag
    }
}

// Function to toggle the LED on PB5
void toggle_led() {
    PORTB ^= (1 << PB5); // Toggle the state of PB5
}

int main() {
    DDRB |= (1 << PB5); // Set PB5 as output

    timer0_init(); // Initialize Timer0 with prescaler
    Serial_begin(9600); // Initialize UART communication

    while (1) {
        // Wait for Timer0 compare match
        timercounter = TCNT0; // Read the Timer0 counter value
        SerialPrintf("TimerCounter = %d\r\n",timercounter); // Print the counter value over serial communication
        toggle_led(); // Toggle the LED state
        wait_for_timer0_match(1000); // Wait for 1000 Timer0 compare matches (approximately 1 second)
    }

    return 0;
}
