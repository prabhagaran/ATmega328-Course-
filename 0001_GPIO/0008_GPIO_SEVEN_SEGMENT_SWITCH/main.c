/*
 * 0007_GPIO_SEVEN_SEGMENT_DISPLAY.c
 *
 * Created: 31-08-2023 02:30:21 PM
 * Author : vingyan
 * Description: This program demonstrates how to interface a common-anode seven-segment display
 *              with an AVR microcontroller. It sequentially displays digits from 0 to 9 in a loop,
 *              incrementing and then decrementing the numbers with a delay of 1 second between each
 *              increment and decrement operation.
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

// Function to print numbers 0 through 9 on the seven-segment display
void printNumbers(int num)
{
    // Switch statement to select and display each digit
    switch (num)
    {
        case 0:
            PORTD &= ~(1U << SEG_A_PIN);
            PORTD &= ~(1U << SEG_B_PIN);
            PORTD &= ~(1U << SEG_C_PIN);
            PORTD &= ~(1U << SEG_D_PIN);
            PORTD &= ~(1U << SEG_E_PIN);
            PORTD &= ~(1U << SEG_F_PIN);
            break;
        case 1:
            PORTD &= ~(1U << SEG_B_PIN);
            PORTD &= ~(1U << SEG_C_PIN);
            break;
        case 2:
            PORTD &= ~(1U << SEG_A_PIN);
            PORTD &= ~(1U << SEG_B_PIN);
            PORTD &= ~(1U << SEG_D_PIN);
            PORTD &= ~(1U << SEG_E_PIN);
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
            PORTD &= ~(1U << SEG_F_PIN);
            PORTB &= ~(1U << SEG_G_PIN);
            break;
        case 5:
            PORTD &= ~(1U << SEG_A_PIN);
            PORTD &= ~(1U << SEG_C_PIN);
            PORTD &= ~(1U << SEG_D_PIN);
            PORTD &= ~(1U << SEG_F_PIN);
            PORTB &= ~(1U << SEG_G_PIN);
            break;
        case 6:
            PORTD &= ~(1U << SEG_A_PIN);
            PORTD &= ~(1U << SEG_C_PIN);
            PORTD &= ~(1U << SEG_D_PIN);
            PORTD &= ~(1U << SEG_E_PIN);
            PORTD &= ~(1U << SEG_F_PIN);
            PORTB &= ~(1U << SEG_G_PIN);
            break;
        case 7:
            PORTD &= ~(1U << SEG_A_PIN);
            PORTD &= ~(1U << SEG_B_PIN);
            PORTD &= ~(1U << SEG_C_PIN);
            break;
        case 8:
            PORTD &= ~(1U << SEG_A_PIN);
            PORTD &= ~(1U << SEG_B_PIN);
            PORTD &= ~(1U << SEG_C_PIN);
            PORTD &= ~(1U << SEG_D_PIN);
            PORTD &= ~(1U << SEG_E_PIN);
            PORTD &= ~(1U << SEG_F_PIN);
            PORTB &= ~(1U << SEG_G_PIN);
            break;
        case 9:
            PORTD &= ~(1U << SEG_A_PIN);
            PORTD &= ~(1U << SEG_B_PIN);
            PORTD &= ~(1U << SEG_C_PIN);
            PORTD &= ~(1U << SEG_D_PIN);
            PORTD &= ~(1U << SEG_F_PIN);
            PORTB &= ~(1U << SEG_G_PIN);
            break;
        default:
            all_segment_off();
            break;
    }
}

// Function to increment numbers from 0 to 9 and display them
void incrementNumbers(void)
{
    for(int i = 0; i <= 9; i++)
    {
        printNumbers(i);
        _delay_ms(1000);
        all_segment_off();
    }
}

// Function to decrement numbers from 9 to 0 and display them
void decrementNumbers(void)
{
    for(int j = 9; j >= 0; j--)
    {
        printNumbers(j);
        _delay_ms(1000);
        all_segment_off();
    }
}

int main(void)
{
    // Configure the pins connected to the segments of the seven-segment display as output
    DDRD |= (1U << SEG_A_PIN) | (1U <<SEG_B_PIN) | (1U << SEG_C_PIN) | (1U << SEG_D_PIN) | (1U << SEG_E_PIN) | (1U << SEG_F_PIN
