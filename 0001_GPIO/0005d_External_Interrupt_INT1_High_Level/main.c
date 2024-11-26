/*
 * 0021_external_interrupt.c
 *
 * Created: 20-05-2024
 * Author : vingyan
 * Description: This program uses an external interrupt to control an LED connected to PB5 (Arduino pin 13).
 *              When a button connected to PD3 (INT1) is pressed, the LED turns on, and when the button is released, the LED turns off.
 * 
 * Detailed Explanation:
 * 1. BUTTON_PIN (PD3) is configured as an input with an internal pull-up resistor.
 * 2. LED_PIN (PB5) is configured as an output to control the LED.
 * 3. External interrupt INT1 is configured to trigger on a rising edge (high level).
 * 4. When the button connected to PD3 is pressed or released, an interrupt is triggered.
 * 5. The ISR (Interrupt Service Routine) checks the state of PD3:
 *    - If PD3 is high (button released), the LED is turned on.
 *    - If PD3 is low (button pressed), the LED is turned off.
 * 6. Global interrupts are enabled to ensure the ISR can be triggered.
 */

#include <avr/io.h>          // Include AVR IO definitions
#include <avr/interrupt.h>   // Include AVR interrupt support

// Define the button pin and LED pin
#define BUTTON_PIN PD3 // INT1 (external interrupt 1)
#define LED_PIN PB5

// Function to initialize the external interrupt
void externalInterruptInit() {
    // Set the BUTTON_PIN (PD3) as input
    DDRD &= ~(1 << BUTTON_PIN);

    // Enable the internal pull-up resistor for the BUTTON_PIN
    PORTD |= (1 << BUTTON_PIN);

    // Configure external interrupt INT1 to trigger on rising edge (high level)
    EICRA |= (1 << ISC11) | (1 << ISC10);  // Trigger on rising edge
    EIMSK |= (1 << INT1);  // Enable INT1 interrupt
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
        // This loop runs indefinitely, while the ISR handles the LED control
    }

    return 0;
}

// External interrupt service routine for INT1
ISR(INT1_vect) {
    // Check if the button is released (high level)
    if (PIND & (1 << BUTTON_PIN)) {
        // Button is released; turn on the LED
        PORTB |= (1 << LED_PIN);
    } else {
        // Button is pressed; turn off the LED
        PORTB &= ~(1 << LED_PIN);
    }
}
