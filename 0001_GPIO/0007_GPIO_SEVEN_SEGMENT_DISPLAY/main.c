/*
 * 0007_GPIO_SEVEN_SEGMENT_DISPLAY.c
 *
 * Created: 31-08-2023 02:30:21 PM
 * Author : vingyan
 * Description: This program demonstrates how to interface a common-anode seven-segment display
 *              with an AVR microcontroller. It sequentially displays digits from 0 to 9.
 *              Each segment of the display is controlled by a specific pin of the microcontroller.
 * Notes:

		 The macro constants define the pin assignments for each segment of the seven-segment display.
		 The all_segment_off() function turns off all segments of the display by setting their corresponding pins high.
		 Inside the main loop, each digit from 0 to 9 is displayed sequentially with a delay of 1000 milliseconds (1 second) between each digit.
		 Each digit is displayed by turning on specific segments using port manipulation.
		 The _delay_ms() function from the `<util/delay
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

// Define macro constants for the pin assignments of each segment of the seven-segment display
#define SEG_A_PIN       PD2
#define SEG_B_PIN       PD3
#define SEG_C_PIN       PD4
#define SEG_D_PIN       PD5
#define SEG_E_PIN       PD6
#define SEG_F_PIN       PD7
#define SEG_G_PIN       PB0
#define SEG_DP_PIN      PB1

// Function to turn off all segments of the seven-segment display
void all_segment_off(void)
{
    // Turn off all segments by setting their corresponding pins high
    PORTD |= (1U << SEG_A_PIN) | (1U <<SEG_B_PIN) | (1U << SEG_C_PIN) | (1U << SEG_D_PIN) | (1U << SEG_E_PIN) | (1U << SEG_F_PIN);
    PORTB |= (1U << SEG_G_PIN) | (1U << SEG_DP_PIN);
}

int main(void)
{
    // Configure the pins connected to the segments of the seven-segment display as output
    DDRD |= (1U << SEG_A_PIN) | (1U << SEG_B_PIN) | (1U << SEG_C_PIN) | (1U << SEG_D_PIN) | (1U << SEG_E_PIN) | (1U << SEG_F_PIN);
    DDRB |= (1U << SEG_G_PIN) | (1U << SEG_DP_PIN);

    // Turn off all segments initially
    all_segment_off();

    while (1)
    {
        // Display digits 0 through 9 sequentially with a delay of 1000 milliseconds (1 second) between each digit
        
        // 0
        PORTD &= ~(1U << SEG_A_PIN);
        PORTD &= ~(1U << SEG_B_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        PORTD &= ~(1U << SEG_D_PIN);
        PORTD &= ~(1U << SEG_E_PIN);
        PORTD &= ~(1U << SEG_F_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 1
        PORTD &= ~(1U << SEG_B_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 2
        PORTD &= ~(1U << SEG_A_PIN);
        PORTD &= ~(1U << SEG_B_PIN);
        PORTD &= ~(1U << SEG_D_PIN);
        PORTD &= ~(1U << SEG_E_PIN);
        PORTB &= ~(1U << SEG_G_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 3
        PORTD &= ~(1U << SEG_A_PIN);
        PORTD &= ~(1U << SEG_B_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        PORTD &= ~(1U << SEG_D_PIN);
        PORTB &= ~(1U << SEG_G_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 4
        PORTD &= ~(1U << SEG_B_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        PORTD &= ~(1U << SEG_F_PIN);
        PORTB &= ~(1U << SEG_G_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 5
        PORTD &= ~(1U << SEG_A_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        PORTD &= ~(1U << SEG_D_PIN);
        PORTD &= ~(1U << SEG_F_PIN);
        PORTB &= ~(1U << SEG_G_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 6
        PORTD &= ~(1U << SEG_A_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        PORTD &= ~(1U << SEG_D_PIN);
        PORTD &= ~(1U << SEG_E_PIN);
        PORTD &= ~(1U << SEG_F_PIN);
        PORTB &= ~(1U << SEG_G_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 7
        PORTD &= ~(1U << SEG_A_PIN);
        PORTD &= ~(1U << SEG_B_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 8
        PORTD &= ~(1U << SEG_A_PIN);
        PORTD &= ~(1U << SEG_B_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        PORTD &= ~(1U << SEG_D_PIN);
        PORTD &= ~(1U << SEG_E_PIN);
        PORTD &= ~(1U << SEG_F_PIN);
        PORTB &= ~(1U << SEG_G_PIN);
        _delay_ms(1000);
        all_segment_off();

        // 9
        PORTD &= ~(1U << SEG_A_PIN);
        PORTD &= ~(1U << SEG_B_PIN);
        PORTD &= ~(1U << SEG_C_PIN);
        PORTD &= ~(1U << SEG_D_PIN);
        PORTD &= ~(1U << SEG_F_PIN);
        PORTB &= ~(1U << SEG_G_PIN);
        _delay_ms(1000);
        all_segment_off();
    }
    return 0;
}
