/*
 * 0007_GPIO_SEVEN_SEGMENT_DISPLAY.c
 *
 * Created: 31-08-2023 02:30:21 PM
 * Author : vingyan
 * Description: This program demonstrates how to interface a common-cathode seven-segment display
 *              with an AVR microcontroller. It sequentially displays digits from 0 to 9 in a loop,
 *              incrementing the count each time a button connected to PC0 is pressed.
 */  

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define SEG_A_PIN       PD4
#define SEG_B_PIN       PD5
#define SEG_C_PIN       PD6
#define SEG_D_PIN       PD7
#define SEG_E_PIN       PB0
#define SEG_F_PIN       PB1
#define SEG_G_PIN       PB2
#define SEG_DP_PIN      PB3
int count = 0;

void all_segment_off(void)
{
	PORTD |= (1U << SEG_A_PIN) | (1U <<SEG_B_PIN) |(1U << SEG_C_PIN) | (1U << SEG_D_PIN) | (1U << SEG_E_PIN) | (1U << SEG_F_PIN);
	PORTB |= (1U << SEG_G_PIN) | (1U << SEG_DP_PIN);
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
		     //6
		     PORTD &= ~(1U << SEG_A_PIN);
		     //PORTD &= ~(1U << SEG_B_PIN);
		     PORTD &= ~(1U << SEG_C_PIN);
		     PORTD &= ~(1U << SEG_D_PIN);
		     PORTD &= ~(1U << SEG_E_PIN);
		     PORTD &= ~(1U << SEG_F_PIN);
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
		     PORTD &= ~(1U << SEG_E_PIN);
		     PORTD &= ~(1U << SEG_F_PIN);
		     PORTB &= ~(1U << SEG_G_PIN);
			 break;
	   case 9:
		     //9
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


int main(void)
{
    /* Replace with your application code */
	Serial_begin(9600);
	
	DDRD |= (1U << SEG_A_PIN) | (1U <<SEG_B_PIN) |(1U << SEG_C_PIN) | (1U << SEG_D_PIN) | (1U << SEG_E_PIN) | (1U << SEG_F_PIN);
	DDRB |= (1U << SEG_G_PIN) | (1U << SEG_DP_PIN);
	
	DDRC &= ~(1 << PC0);
	PORTC |= (1 << PC0);
	
	DDRB |= (1U << PB2);
	PORTB |= (1 << PB2);

	DDRB |= (1U << PB5);
	DDRB |= (1U << PB4);

	int buttonState = 0;
	int lastButtonState = 1;
	
	all_segment_off();
    while (1) 
    {
		buttonState = PINC & (1U << PC0);
		
		if(buttonState == 1 && lastButtonState == 0)
		{
			
			PORTB ^= (1U << PB2);
			all_segment_off();
			count = (count + 1) % 10;
			SerialPrintf("Count = %d \r\n",count);
			printNumbers(count);
		}
		
		lastButtonState = buttonState;
		
		_delay_ms(10);
		
	
    }
}

