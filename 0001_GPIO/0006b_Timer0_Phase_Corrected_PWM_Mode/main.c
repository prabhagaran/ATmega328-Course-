/*
 * File: 0006b_Timer0_Phase_Corrected_PWM_Mode.c
 * Author: VINGYAN 
 * Description: This program demonstrates the generation of a PWM signal using Timer/Counter 0 in Phase Corrected PWM mode.
 *              It configures Timer/Counter 0 to generate a PWM waveform on pin OC0A (PD6) using Phase Corrected PWM mode.
 *              The duty cycle of the PWM signal is varied from 0% to 100% and back.
 * Notes:

		 This program demonstrates the generation of a PWM (Pulse Width Modulation) signal using Timer/Counter 0 in Phase Corrected PWM mode.
		 It configures Timer/Counter 0 to generate a PWM waveform on pin OC0A (PD6) with a varying duty cycle.
		 The duty cycle of the PWM signal is smoothly increased from 0% to 100% and then decreased back to 0%.
		 Timer/Counter 0 is configured in Phase Corrected PWM mode with a prescaler of 64, resulting in a PWM frequency determined by the CPU frequency and the prescaler value.
		 The duty cycle is controlled by adjusting the value of OCR0A, which determines the point in the PWM period at which the output changes state.
 */ 

#define F_CPU 16000000 // Define the clock frequency for delay functions
#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

int main(void) {
    // Configure Timer/Counter 0 in Phase Corrected PWM mode, non-inverting
    TCCR0A |= (1 << WGM00) | (1 << COM0A1);
    TCCR0B |= (1 << CS01) | (1 << CS00); // Set prescaler to 64

    // Set PD6 as output for OC0A (PWM output)
    DDRD |= (1 << PORTD6);

    while (1) {
        // Increase PWM duty cycle from 0% to 100%
        for (int i = 0; i <= 254; i++) {
            OCR0A = i;
            _delay_ms(50);
        }

        // Decrease PWM duty cycle from 100% to 0%
        for (int i = 254; i >= 0; i--) {
            OCR0A = i;
            _delay_ms(50);
        }
    }

    return 0;
}
