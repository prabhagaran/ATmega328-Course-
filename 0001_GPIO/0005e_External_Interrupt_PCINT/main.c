/*
 * 0021_pin_change_interrupt.c
 *
 * Created: 20-05-2024
 * Author : vingyan
 * Description: This program uses pin change interrupts to control an LED connected to PB5 (Arduino pin 13).
 *              When a button connected to PB2 is pressed, the LED turns on, and when the button is released, the LED turns off.
 * 
 * Detailed Explanation:
 * 1. PCINT_PIN (PB2) is configured to trigger a pin change interrupt.
 * 2. LED_PIN (PB5) is configured as an output to control the LED.
 * 3. When the button connected to PB2 is pressed or released, an interrupt is triggered.
 * 4. The ISR (Interrupt Service Routine) checks the state of PB2:
 *    - If PB2 is high (button pressed), the LED is turned on.
 *    - If PB2 is low (button released), the LED is turned off.
 * 5. Global interrupts are enabled to ensure the ISR can be triggered.
 */

#include <avr/io.h>          // Include AVR IO definitions
#include <avr/interrupt.h>   // Include AVR interrupt support

// Define the pin for which you want to enable the pin change interrupt
#define PCINT_PIN PB2  // Example pin: PB2

// Define the LED pin
#define LED_PIN PB5

// Function to initialize pin change interrupt
void PCINT_init() {
    // Enable the Pin Change Interrupt for PCINT0 (which covers PB0 to PB7)
    PCICR |= (1 << PCIE0);

    // Set the PCMSK0 register to enable pin change interrupt for the specific pin
    PCMSK0 |= (1 << PCINT_PIN);
}

// Function to initialize the LED pin
void ledInit() {
    // Set the LED_PIN (PB5) as an output
    DDRB |= (1 << LED_PIN);
}

int main(void) {
    PCINT_init(); // Initialize pin change interrupt
    ledInit();    // Initialize LED pin

    // Enable global interrupts
    sei();

    while (1) {
        // Your main application code can go here
        // This loop runs indefinitely, while the ISR handles the LED control
    }

    return 0;
}

// Pin change interrupt service routine
ISR(PCINT0_vect) {
    // Check the specific pin that caused the interrupt
    if (PINB & (1 << PCINT_PIN)) {
        // Pin changed from low to high (button pressed)
        // Turn on the LED
        PORTB |= (1 << LED_PIN);
    } else {
        // Pin changed from high to low (button released)
        // Turn off the LED
        PORTB &= ~(1 << LED_PIN);
    }
}
