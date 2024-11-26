/*
 * Description: AVR code for a simple dice rolling game using a 7-segment display and a push button.
 *              Pressing the button simulates rolling a dice, and the result is displayed on the 7-segment display.
 *              Requires AVR microcontroller, 7-segment display, and a push button.
 * Author: vingyan
 * Date: [Date]
 */
#define F_CPU 16000000UL // Define the clock frequency (16 MHz)

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // Required for random number generation

#define SEG_A_PIN       PD4
#define SEG_B_PIN       PD5
#define SEG_C_PIN       PD6
#define SEG_D_PIN       PD7
#define SEG_E_PIN       PB0
#define SEG_F_PIN       PB1
#define SEG_G_PIN       PB2
#define SEG_DP_PIN      PB3

#define BUTTON_PIN      PC0

void all_segment_off(void)
{
	PORTD |= (1U << SEG_A_PIN) | (1U << SEG_B_PIN) |(1U << SEG_C_PIN) | (1U << SEG_D_PIN) ;
	PORTB |= (1U << SEG_E_PIN) | (1U << SEG_F_PIN) |(1U << SEG_G_PIN) | (1U << SEG_DP_PIN);
}

void initializeIO() {
	// Set buttons as inputs and enable pull-up resistors
	DDRD |= (1U << SEG_A_PIN) | (1U << SEG_B_PIN) | (1U << SEG_C_PIN) | (1U << SEG_D_PIN) ;
	DDRB |= (1U << SEG_E_PIN) | (1U << SEG_F_PIN) | (1U << SEG_G_PIN) | (1U << SEG_DP_PIN);
	
	 DDRC &= ~(1 << BUTTON_PIN);
	 PORTC |= (1 << BUTTON_PIN);
}
void printNumbers(int num)
{
	switch (num)
	{
		case 0:
		PORTD &= ~(1U << SEG_A_PIN);
		PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		PORTD &= ~(1U << SEG_D_PIN);
		PORTB &= ~(1U << SEG_E_PIN);
		PORTB &= ~(1U << SEG_F_PIN);
		break;
		case 1:
		PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		break;
		case 2:
		PORTD &= ~(1U << SEG_A_PIN);
		PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_D_PIN);
		PORTB &= ~(1U << SEG_E_PIN);
		PORTB &= ~(1U << SEG_G_PIN);
		break;
		case 3:
		PORTD &= ~(1U << SEG_A_PIN);
		PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		PORTD &= ~(1U << SEG_D_PIN);
		PORTB &= ~(1U << SEG_G_PIN);
		break;
		case 4:
		
		PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		PORTB &= ~(1U << SEG_F_PIN);
		PORTB &= ~(1U << SEG_G_PIN);
		break;
		case 5:
		PORTD &= ~(1U << SEG_A_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		PORTD &= ~(1U << SEG_D_PIN);
		PORTB &= ~(1U << SEG_F_PIN);
		PORTB &= ~(1U << SEG_G_PIN);
		break;
		case 6:
		//6
		PORTD &= ~(1U << SEG_A_PIN);
		//PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		PORTD &= ~(1U << SEG_D_PIN);
		PORTB &= ~(1U << SEG_E_PIN);
		PORTB &= ~(1U << SEG_F_PIN);
		PORTB &= ~(1U << SEG_G_PIN);
		break;
		case 7:
		//7
		PORTD &= ~(1U << SEG_A_PIN);
		PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		break;
		case 8:
		//8
		PORTD &= ~(1U << SEG_A_PIN);
		PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		PORTD &= ~(1U << SEG_D_PIN);
		PORTB &= ~(1U << SEG_E_PIN);
		PORTB &= ~(1U << SEG_F_PIN);
		PORTB &= ~(1U << SEG_G_PIN);
		break;
		case 9:
		//9
		PORTD &= ~(1U << SEG_A_PIN);
		PORTD &= ~(1U << SEG_B_PIN);
		PORTD &= ~(1U << SEG_C_PIN);
		PORTD &= ~(1U << SEG_D_PIN);
		PORTB &= ~(1U << SEG_F_PIN);
		PORTB &= ~(1U << SEG_G_PIN);
		break;
		default:
		//all_segment_off();
		break;
	}
	
	
}

int rollDice() {
	// Generate a random number between 1 and 6
	return (rand() % 6) + 1;
}
int isButtonPressed() {
	// Read the state of the button
	return !(PINC & (1 << BUTTON_PIN));
}

int main(void) {
	initializeIO();
	srand(42); // Seed the random number generator with a fixed value

	while (1) {
		// Check if the button is pressed
		
		for(int i = 0; i <= 6;i++)
		{
			all_segment_off();
			printNumbers(i);
			_delay_ms(100);
		}
		
		if (isButtonPressed()) {
			// Simulate rolling the dice
			all_segment_off();
			int result = rollDice();

			// Display the result on LEDs
			printNumbers(result);

			// Wait for a moment before allowing another roll
			_delay_ms(1000);

			// Wait for the button to be released
			while (isButtonPressed()) {}
		}
	}
	return 0;
}
