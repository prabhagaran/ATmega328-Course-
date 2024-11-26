/*
 * File: button_interrupt.c
 * Created: [Date]
 * Author: vingyan
 * Description: This program toggles an LED connected to PB5 when a button connected to PC0 is pressed three times consecutively.
 *              It uses polling to detect button presses and debounces the button input.
 * 
 * Detailed Explanation:
 * 1. F_CPU is defined as 16 MHz for delay functions.
 * 2. BUTTON_PIN (PC0) is set as input, and the pull-up resistor is enabled.
 * 3. PB5 is set as an output for the LED.
 * 4. currentState and prevState variables are used to track button states.
 * 5. transitionCount counts consecutive transitions of button state.
 * 6. Inside the while loop:
 *    a. The button state is read.
 *    b. If there's a transition, the transitionCount is incremented.
 *    c. If three consecutive transitions occur, the LED is toggled.
 *    d. The loop includes a small delay for stability and responsiveness.
 */

#define F_CPU 16000000 // Define the clock frequency for delay functions

#include <avr/io.h>     // AVR Standard I/O Library
#include <util/delay.h> // AVR Delay Functions Library

#define BUTTON_PIN PC0 // Define the button pin

int main(void) {
    // Set the button pin as input and enable pull-up resistor
    DDRC &= ~(1 << BUTTON_PIN); // Set PC0 as input
    //PORTC |= (1 << BUTTON_PIN); // Enable pull-up resistor (not needed if internal pull-up is used)
    DDRD |= (1U << PB5); // Set PB5 as output for LED

    int currentState = 1; // Initialize as released
    int prevState = 1;    // Previous state

    int transitionCount = 0; // Count of consecutive transitions

    while (1) { // Infinite loop
        int buttonState = PINC & (1 << BUTTON_PIN); // Read the button state

        if (buttonState != currentState) { // If there's a transition
            if (buttonState == prevState) { // If the current state matches the previous state
                transitionCount++; // Increment the transition count
                if (transitionCount >= 3) { // If three consecutive transitions occurred
                    // Valid transition detected, perform action
                    PORTB ^= (1 << PB5); // Toggle the LED
                    currentState = buttonState; // Update the current state
                    transitionCount = 0; // Reset the transition count
                }
            } else { // If the current state doesn't match the previous state
                // Reset the transition count
                transitionCount = 0;
                prevState = buttonState; // Update the previous state
            }
        }

        _delay_ms(10); // Small delay for stability and responsiveness
    }

    return 0;
}
