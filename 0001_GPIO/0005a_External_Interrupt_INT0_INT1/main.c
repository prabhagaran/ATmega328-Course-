/*
 * File: external_interrupt.c
 * Created: [Date]
 * Author: vingyan
 * Description: This program demonstrates the usage of an external interrupt to control an LED.
 *              When a button connected to PD2 (INT0) is pressed, the LED connected to PB5 is turned on,
 *              and when the button is released, the LED is turned off.
 * 
 * Detailed Explanation:
 * 1. BUTTON_PIN (PD2) is configured as an input with an internal pull-up resistor enabled.
 * 2. LED_PIN (PB5) is configured as an output to control the LED.
 * 3. External interrupt INT0 is configured to trigger on a falling edge (low level) of the button signal.
 * 4. When the button connected to PD2 is pressed (low level), an interrupt is triggered.
 * 5. The ISR (Interrupt Service Routine) checks the state of PD2:
 *    - If PD2 is low (button pressed), the LED is turned on.
 *    - If PD2 is high (button released), the LED is turned off.
 * 6. Global interrupts are enabled to ensure the ISR can be triggered.
 */

#include <avr/io.h>          // Include AVR IO definitions
#include <avr/interrupt.h>   // Include AVR interrupt support

// Define the button pin and LED pin
#define BUTTON_PIN PD2 // Pin where the button is connected
#define LED_PIN PB5    // Pin where the LED is connected

// Function to initialize external interrupt INT0
void externalInterruptInit() {
    // Set the BUTTON_PIN (PD2) as input
    DDRD &= ~(1 << BUTTON_PIN);

    // Enable the internal pull-up resistor for the BUTTON_PIN
    PORTD |= (1 << BUTTON_PIN);

    // Configure the external interrupt INT0 to trigger on falling edge
    EICRA |= (1 << ISC01);  // Trigger on falling edge
    EICRA &= ~(1 << ISC00); // Trigger on falling edge
    EIMSK |= (1 << INT0);   // Enable INT0 interrupt
}

// Function to initialize the LED pin
void ledInit() {
    // Set the LED_PIN (PB5) as an output
    DDRB |= (1 << LED_PIN);
}

int main(void) {
    externalInterruptInit(); // Initialize external interrupt
    ledInit();               // Initialize LED pin

    // Enable global interrupts
    sei();

    while (1) {
        // Your main application code can go here
        // In this case, it just waits for interrupts to occur
    }
    return 0;
}

// External interrupt service routine for INT0
ISR(INT0_vect) {
    // Check if the button is pressed
    if (!(PIND & (1 << BUTTON_PIN))) {
        // Button is pressed; turn on the LED
        PORTB |= (1 << LED_PIN);
    } else {
        // Button is released; turn off the LED
        PORTB &= ~(1 << LED_PIN);
    }
}
