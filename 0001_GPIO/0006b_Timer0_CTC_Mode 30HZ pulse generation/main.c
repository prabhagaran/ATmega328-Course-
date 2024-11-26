/*
 * File: pwm_generation.c
   Author: vingyan
 * Description: This program generates a PWM signal using Timer/Counter 0 in CTC mode.
 *              It configures Timer/Counter 0 to generate a PWM waveform on pin OC0B (PD5) using CTC mode.
 *              The duty cycle of the PWM signal can be adjusted by changing the value of OCR0A.
 *Notes:

		 This program generates a PWM (Pulse Width Modulation) signal using Timer/Counter 0 in CTC (Clear Timer on Compare Match) mode.
		 It configures Timer/Counter 0 to generate a PWM waveform on pin OC0B (PD5).
		 The duty cycle of the PWM signal can be adjusted by changing the value of OCR0A. A higher value results in a lower duty cycle, and vice versa.
		 The prescaler is set to 1024, which determines the PWM frequency. Adjust the prescaler value to change the PWM frequency.
		 The program uses a polling method to check if the Timer/Counter 0 compare match flag (OCF0A) is set. This flag indicates when the PWM cycle completes.
 *
 * 
 */

#define F_CPU 16000000 // Define the clock frequency for delay functions
#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

int main(void) {
    DDRD |= (1 << DDD5); // Set PD5 as output for OC0B (PWM output)
    DDRD |= (1 << DDD6); // Set PD6 as output for OC0A (optional)

    // Set CTC mode for Timer/Counter 0 (WGM01 = 1)
    TCCR0A |= (1 << WGM01);

    // Set toggle mode for OC0B (COM0B1 = 0, COM0B0 = 1)
    TCCR0A |= (1 << COM0A0) | (1 << COM0B0);

    // Set the compare value (adjust as needed)
    OCR0A = 255; // Example value

    // Set the prescaler (adjust as needed)
    TCCR0B |= (1 << CS02) | (1 << CS00); // Prescaler = 1024

    while (1) {
        // Polling method: Check if Timer/Counter 0 compare match flag is set
        if (TIFR0 & (1 << OCF0A)) {
            // Clear the compare match flag by writing a logic one to it
            TIFR0 |= (1 << OCF0A);

            // Optional delay to visualize the PWM waveform
            _delay_ms(500);
        }

        // Your main code here
    }

    return 0;
}
