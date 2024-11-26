/*
 * File: timer_led_toggle.c
 * Description: This program toggles an LED connected to pin PD5 using Timer0 interrupts.
 *              It initializes Timer0 in CTC mode with a prescaler and sets up the LED pin as output.
 *              The LED is toggled at a regular interval determined by Timer0 compare match interrupts.
 *              The Timer0 is configured to generate interrupts approximately every 100 milliseconds.
 *              The counter value of Timer0 and OCR0A value (compare match register) are printed over UART for monitoring purposes.
 *Notes:
	 This program toggles an LED connected to pin PD5 using Timer0 interrupts.
	 It initializes Timer0 in CTC (Clear Timer on Compare Match) mode with a prescaler to generate interrupts approximately every 100 milliseconds.
	 The LED pin (PD5) is configured as an output.
	 The Timer0 compare match interrupt is used to toggle the LED at a regular interval.
	 The counter value of Timer0 and the OCR0A value (compare match register) are printed over UART for monitoring purposes.
 * Author: [Your Name]
 */

#include "uart.h" // Include UART library header file
#include <avr/io.h> // AVR Standard I/O Library
#include <avr/interrupt.h> // AVR Interrupt Handling Library
#include <util/delay.h> // AVR Delay Functions Library

uint16_t timer_Counter = 0; // Variable to store the timer counter value
uint16_t OCReg = 0; // Variable to store the OCR0A value (compare match register)

#define DELAY_MS 100 // 100 milliseconds delay

// Function to initialize Timer0 in CTC mode with prescaler
void timer0_init() {
    TCCR0A |= (1 << WGM01); // Set WGM01 bit to enable CTC mode
    OCR0A = (F_CPU / 10000) * DELAY_MS / 1024 - 1; // Set the value for compare match for 100 ms delay with prescaler 64
    OCReg = (F_CPU / 10000) * DELAY_MS / 1024 - 1; // Store the OCR0A value
    TIMSK0 |= (1 << OCIE0A); // Enable Timer0 compare match interrupt
    TCCR0B |= (1 << CS02) | (1 << CS00); // Set prescaler to 64
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
    Serial_begin(9600); // Initialize UART communication

    timer0_init(); // Initialize Timer0

    while (1) {
        // Your main program loop (do other tasks if needed)
        SerialPrintf("Timer = %d OCR0A = %d\r\n", timer_Counter, OCReg); // Print Timer0 counter and OCR0A value over serial communication
    }

    return 0;
}
