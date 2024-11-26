/*
 * Description: AVR code for controlling a 7-segment display with two buttons.
 *              Button 1 increments the displayed number, and Button 2 decrements it.
 *              The displayed number cycles from 0 to 9 and vice versa.
 *              Requires AVR microcontroller, 7-segment display, and two push buttons.
 * Author: vingyan
 * Date: [Date]
 */
#define F_CPU 16000000UL // Define the clock frequency

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON1_PIN PC0
#define BUTTON2_PIN PC1

#define LED1_PIN 4
#define LED2_PIN 5


#define SEG_A_PIN       PD4
#define SEG_B_PIN       PD5
#define SEG_C_PIN       PD6
#define SEG_D_PIN       PD7
#define SEG_E_PIN       PB0
#define SEG_F_PIN       PB1
#define SEG_G_PIN       PB2
#define SEG_DP_PIN      PB3
int count = 0;

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

void all_segment_off(void) // Code to turn off all segments
{
	PORTD |= (1U << SEG_A_PIN) | (1U << SEG_B_PIN) |(1U << SEG_C_PIN) | (1U << SEG_D_PIN) ;
	PORTB |= (1U << SEG_E_PIN) | (1U << SEG_F_PIN) |(1U << SEG_G_PIN) | (1U << SEG_DP_PIN);
}

// Function to initialize IO configurations
void initializeIO() {
	// Set buttons as inputs and enable pull-up resistors
	DDRC &= ~((1 << BUTTON1_PIN) | (1 << BUTTON2_PIN));
	PORTC |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN);
	DDRD |= (1U << SEG_A_PIN) | (1U << SEG_B_PIN) | (1U << SEG_C_PIN) | (1U << SEG_D_PIN) ;
	DDRB |= (1U << SEG_E_PIN) | (1U << SEG_F_PIN) | (1U << SEG_G_PIN) | (1U << SEG_DP_PIN);

	// Set LEDs as outputs
	DDRB |= (1 << LED1_PIN) | (1 << LED2_PIN);
}

int debounceButton(uint8_t buttonPin) {
	int prevState = 1;
	int currentState = 0;
	int stableCount = 0;

	while (stableCount < 5) {
		currentState = PINC & (1 << buttonPin);
		if (currentState == prevState) {
			stableCount++;
			} else {
			stableCount = 0;
		}
		prevState = currentState;
		_delay_ms(10); // Small delay for stability and responsiveness
	}

	return currentState;
}

int main(void) {
	initializeIO();

	while (1) {
		// Check if Button 1 is pressed
		if (debounceButton(BUTTON1_PIN) == 0) {
			count = (count + 1) % 10;
			all_segment_off();
			printNumbers(count);
			
		}

		// Check if Button 2 is pressed
		if (debounceButton(BUTTON2_PIN) == 0) {
			count = (count - 1 + 10) % 10;
			all_segment_off();
			printNumbers(count);
		}
	}

	return 0;
}
