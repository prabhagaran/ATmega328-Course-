/*
 * 0021_8bit_timer_normal_mode_interrupt.c
 *
 * Created: 20-09-2023 03:49:30 PM
 * Author : vingyan
 * Description: This program toggles an LED connected to PB5 (Arduino pin 13) using Timer0 in normal mode.
 *              The LED is toggled approximately every second using an interrupt service routine.
 * 
 * Timer Configuration:
 * - Prescaler: 1024
 * - Timer0 clock: F_CPU / 1024 = 16 MHz / 1024 = 15.625 kHz
 * - Timer0 overflow frequency: 15.625 kHz / 256 ? 61.035 Hz
 * - Number of overflows to toggle LED: 50
 * - Toggle interval: 50 / 61.035 Hz ? 0.8192 seconds (819.2 ms)
 * 
 * Detailed Explanation:
 * 1. The program configures PB5 as an output pin for the LED.
 * 2. Timer0 is configured in normal mode with a prescaler of 1024.
 * 3. The main loop does nothing, as the LED toggling is handled by the ISR for Timer0 overflow.
 * 4. Each time an overflow occurs, the ISR increments the overflow counter (count).
 * 5. When the overflow counter reaches 50, the ISR toggles the LED and resets the counter.
 * 6. This results in the LED toggling approximately every 819.2 milliseconds.
 */

#define F_CPU 16000000  // Define the CPU clock frequency as 16 MHz
#include <avr/io.h>     // Include AVR IO definitions
#include <util/delay.h> // Include delay functions
#include <avr/interrupt.h> // Include interrupt support

// Global variable to count the number of Timer0 overflows
volatile uint8_t count = 0;

int main(void)
{
    // Set PB5 as an output pin (usually connected to the onboard LED on many Arduino boards)
    DDRB |= (1U << PB5);
    
    // Configure Timer0
    TCCR0B |= (1U << CS02) | (1U << CS00); // Set prescaler to 1024 (Timer0 clock = F_CPU / 1024)
    
    // Enable Timer0 overflow interrupt
    TIMSK0 |= (1U << TOIE0);
    
    // Enable global interrupts
    sei();
    
    while (1) 
    {
        // Main loop does nothing, all action happens in ISR
    }
}

// Interrupt Service Routine (ISR) for Timer0 overflow
ISR(TIMER0_OVF_vect)
{
    count++; // Increment overflow counter
    
    // Check if 50 overflows have occurred (approximately 1 second with 1024 prescaler)
    if(count == 50)
    {
        PORTB ^= (1U << PB5); // Toggle the LED connected to PB5
        count = 0; // Reset the overflow counter
    }
}
