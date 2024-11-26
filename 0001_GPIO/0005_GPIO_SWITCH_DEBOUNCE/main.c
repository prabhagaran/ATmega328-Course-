#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN 0

int main(void) {
	// Set the button pin as input and enable pull-up resistor
	DDRC &= ~(1 << BUTTON_PIN);
	PORTC |= (1 << BUTTON_PIN);
	DDRB |= (1U << PB0);

	int buttonState = 0;
	int lastButtonState = 1;

	while (1) {
		// Read the button state
		buttonState = PINC & (1 << BUTTON_PIN);

		// Check for button press (Low to High transition)
		if (buttonState == 1 && lastButtonState == 0) {
			// Button press detected, do something
			// For example, toggle an LED
			PORTB ^= (1 << PB0);
		}

		// Store the current button state for comparison in the next loop
		lastButtonState = buttonState;
	}

	return 0;
}
