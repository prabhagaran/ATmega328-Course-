/*
 * File: timer_led_toggle.c
 * Author: vingyan
 * Description: This program toggles an LED connected to pin PD5 using Timer0 interrupts.
 *              It initializes Timer0 in CTC mode with a prescaler and sets up the LED pin as output.
 *              The LED is toggled at a regular interval determined by Timer0 compare match interrupts.
 *              The Timer0 is configured to generate interrupts approximately every 100 milliseconds.
 *              The counter value of Timer0 and the number of LED toggles are printed over UART for monitoring purposes.
 * Notes:

		 This program toggles an LED connected to pin PD5 using Timer0 interrupts.
		 It initializes Timer0 in CTC (Clear Timer on Compare Match) mode with a prescaler to generate interrupts approximately every 100 milliseconds.
		 The LED pin (PD5) is configured as an output.
		 The Timer0 compare match interrupt is used to toggle the LED at a regular interval.
		 The Timer0 counter value and the number of LED toggles are printed over UART for monitoring purposes.
 */

#include "uart.h" // Include UART library header file
#include <avr/io.h> // AVR Standard I/O Library
#include <avr/interrupt.h> // AVR Interrupt Handling Library
#include <util/delay.h> // AVR Delay Functions Library

uint16_t timer_Counter = 0; // Variable to store the timer counter value
uint8_t TCN = 0; // Variable to store the Timer0 counter value

// Function to initialize Timer0 in CTC mode with prescaler
void timer0_init() {
    TCCR0A |= (1 << WGM01); // Set WGM01 bit to enable CTC mode
    OCR0A = (F_CPU / 10000) * 100 / 1024 - 1; // Set the value for compare match for 1 ms delay with prescaler 64
    TIMSK0 |= (1 << OCIE0A); // Enable Timer0 compare match interrupt
    TCCR0B |= (1 << CS02) | (1 << CS01) | (1 << CS00); // Set prescaler to 64
    sei(); // Enable global interrupts
}

// Timer0 compare match ISR (Interrupt Service Routine)
ISR(TIMER0_COMPA_vect) {
    // Toggle the LED on PD5 (pin 13 on Arduino Uno)
    timer_Counter++;
    if (timer_Counter == 100) {
        PORTB ^= (1 << PD5); // Toggle the LED state
        timer_Counter = 0; // Reset the timer counter
    }
}

int main() {
    DDRB |= (1 << PD5); // Set PD5 as output for the LED
    DDRD &= ~(1 << PD4); // Set PD4 as input
    PORTD |= (1 << PD4); // Enable internal pull-up resistor for PD4
    Serial_begin(9600); // Initialize UART communication

    timer0_init(); // Initialize Timer0

    while (1) {
        TCN = TCNT0; // Read Timer0 counter value
        // Your main program loop (do other tasks if needed)
        SerialPrintf("TimerCounterValue = %d, TimerValue = %d\r\n", TCN, timer_Counter); // Print Timer0 counter value and LED toggle count over serial communication
    }

    return 0;
}
