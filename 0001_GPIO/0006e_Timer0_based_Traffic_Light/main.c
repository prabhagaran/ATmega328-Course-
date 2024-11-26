/*
 * File:    Timer_LED_Blink.c
 * Author:  vingyan
 * Date:    May 20, 2024
 * Purpose: Toggle an LED using Timer0 interrupts with a delay of 100 milliseconds.
 * 
 * Hardware Configuration:
 * - Connect an LED to pin PB5 (or any other pin as desired)
 * 
 * Description:
 * This program initializes Timer0 in CTC (Clear Timer on Compare Match) mode with a prescaler of 1024.
 * Timer0 generates an interrupt every 1 millisecond. The number of milliseconds is counted using a volatile
 * variable 'msCounter'. The main loop toggles the LED every 100 milliseconds by calling the 'Timer0_DelayMS'
 * function. The LED connected to PB5 is toggled by XORing the output register value with (1 << LED).
 * 
 * Notes:
 * - Adjust the prescaler value if different delay intervals are required.
 * - Ensure that the LED is connected to the correct pin specified in the 'LED' macro.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED PB5

volatile uint16_t msCounter = 0;

// Function to initialize Timer0
void Timer0_Init() {
    TCCR0A = (1 << WGM01);      // Set Timer/Counter0 to CTC mode
    TCCR0B = (1 << CS02);       // Prescaler 1024
    OCR0A = 250 - 1;            // Set compare value for 1ms interrupt at 16MHz with 1024 prescaler
    TIMSK0 = (1 << OCIE0A);     // Enable Timer/Counter0 Output Compare Match A Interrupt
}

// Function to generate a delay in milliseconds using Timer0
void Timer0_DelayMS(uint16_t milliseconds) {
    msCounter = 0;
    while (msCounter < milliseconds) {
        // Wait for the desired number of milliseconds
    }
}

// Timer0 compare match ISR (Interrupt Service Routine)
ISR(TIMER0_COMPA_vect) {
    msCounter++;    // Increment the millisecond counter
}

int main() {
    DDRB |= (1 << LED); // Set PB5 as an output for the LED

    // Initialize Timer0
    Timer0_Init();

    // Enable global interrupts
    sei();

    while (1) {
        PORTB ^= (1 << LED);    // Toggle the LED
        Timer0_DelayMS(100);    // Delay for 100 milliseconds
    }

    return 0;
}
