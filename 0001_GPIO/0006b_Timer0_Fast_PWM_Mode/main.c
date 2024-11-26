/*
 * File: 0006b_Timer0_Fast_PWM_Mode.c
 Author: VINGYAN 
 * Description: This program demonstrates the generation of a PWM signal using Timer/Counter 0 in Fast PWM mode.
 *              It configures Timer/Counter 0 to generate a PWM waveform on pin OC0A (PD6) using Fast PWM mode.
 *              The duty cycle of the PWM signal is varied from 0% to 100% and back.
 * Notes:
		 This program demonstrates the generation of a PWM (Pulse Width Modulation) signal using Timer/Counter 0 in Fast PWM mode.
		 It configures Timer/Counter 0 to generate a PWM waveform on pin OC0A (PD6) with a varying duty cycle.
		 The duty cycle of the PWM signal is smoothly increased from 0% to 100% and then decreased back to 0%.
		 Timer/Counter 0 is configured in Fast PWM mode with a prescaler of 64, resulting in a PWM frequency determined by the CPU frequency and the prescaler value.
		 The duty cycle is controlled by adjusting the value of OCR0A, which determines the point in the PWM period at which the output changes state.
 *
 */ 

#define F_CPU 16000000 // Define the clock frequency for delay functions
#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

int main(void) {
    DDRD |= (1 << PORTD6); // Set PD6 as output for OC0A (PWM output)

    // Configure Timer/Counter 0 in Fast PWM mode, non-inverting
    TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);

    // Set the prescaler to 64
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler set to 64

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
