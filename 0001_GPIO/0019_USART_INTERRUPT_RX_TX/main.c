/*
 * File: 0019_USART_INTERRUPT_RX_TX.c
 * Description: AVR code for USART communication with interrupt-driven RX and TX.
 * Created: 07-09-2023 02:14:05 PM
 * Author: vingyan
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t receiverbuffer;
volatile uint8_t transmitterbuffer;
uint8_t R_Indicatorflg;
uint8_t L_Indicatorflg;
uint8_t H_flag;
uint8_t F_H_flag;
uint8_t F_B_flag;
void uartInit(uint32_t baudRate)
{
	uint16_t ubrr = (F_CPU / (16 * baudRate)) - 1;
	
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	UCSR0C = (1U << UCSZ01) | (1U << UCSZ00);
	UCSR0B = (1U << RXEN0)  | (1U << TXEN0);
	
	sei();
	
}

void transmitterInterrupt(uint8_t data)
{
	
	transmitterbuffer = data;
	UCSR0B |= (1U << UDRIE0);
}



int main(void)
{
    /* Replace with your application code */
	DDRB |= (1U << PB4);
	DDRB |= (1U << PB5);
	
	
	DDRD |= (1U << PD3);
	DDRD |= (1U << PD4);
	DDRD |= (1U << PD5);
	DDRD |= (1U << PD6);
	
	uartInit(9600);
	UCSR0B |= (1U << RXCIE0);
	
    while (1) 
    {
		if(F_H_flag == 1 && H_flag == 1)
		{
			PORTB |=  (1U << PB4) | (1U << PB5);
			_delay_ms(500);
			PORTB &= ~(1U << PB4) & ~(1U << PB5);
			_delay_ms(500);
		
		}
		else if(F_H_flag == 1 && H_flag == 0)
		{
			PORTB &=  ~(1U << PB4) & ~(1U << PB5);
			
			PORTB &= ~(1U << PB4) & ~(1U << PB5);
			
		}
		
		if (R_Indicatorflg == 1 && L_Indicatorflg == 0)
		{
			PORTB &= ~(1U << PB5);
			PORTB |= (1U << PB4);
			_delay_ms(500);
			PORTB &= ~(1U << PB5);
			PORTB &= ~(1U << PB4);
			_delay_ms(500);
			
		}
		else if (R_Indicatorflg == 0 && L_Indicatorflg == 1)
		{
			PORTB &= ~(1U << PB4);
			PORTB |= (1U << PB5);
			_delay_ms(500);
			PORTB &= ~(1U << PB4);
			PORTB &= ~(1U << PB5);
			_delay_ms(500);
			
		}
		
		
		else if(R_Indicatorflg == 0 && L_Indicatorflg == 0)
		{
			PORTB &=  ~(1U << PB4) & ~(1U << PB5);
			
			PORTB &= ~(1U << PB4) & ~(1U << PB5);
			
		}
		
    }
	return 0;
}

ISR(USART_RX_vect)
{
	receiverbuffer = UDR0;
	transmitterInterrupt(receiverbuffer);
	if(receiverbuffer == 'F')
	{
		F_B_flag = 1;
		R_Indicatorflg = 0;
		L_Indicatorflg = 0;
		
		
		PORTD |=  (1U << PD3); 
		PORTD |=  (1U << PD5);
		PORTD &= ~(1U << PD4); 
		PORTD &= ~(1U << PD6);	
	}
	else if(receiverbuffer == 'B')
	{
		F_B_flag = 1;
		R_Indicatorflg = 0;
		L_Indicatorflg = 0;
	
		
		PORTD &= ~(1U << PD3);
		PORTD &= ~(1U << PD5);
		PORTD |=  (1U << PD4); 
		PORTD |=  (1U << PD6);
		
		
	}
	else if(receiverbuffer == 'L')
	{
		R_Indicatorflg = 0;
		L_Indicatorflg = 1;
		F_B_flag = 0;
		
		PORTD |=  (1U << PD3);
		PORTD &= ~(1U << PD5);
		PORTD &= ~(1U << PD4);
		PORTD |=  (1U << PD6);
		
		
		
	}
	else if(receiverbuffer == 'R')
	{
		R_Indicatorflg = 1;
		L_Indicatorflg = 0;
		F_B_flag = 0;
		
		PORTD &= ~(1U << PD3);
		PORTD |=  (1U << PD5);
		PORTD |=  (1U << PD4);
		PORTD &= ~(1U << PD6);
		
		
	}
	
	
	else if(receiverbuffer == 'S')
	{
		F_B_flag = 1;
		PORTD &= ~(1U << PD4);
		PORTD &= ~(1U << PD6);
		PORTD &= ~(1U << PD3);
		PORTD &= ~(1U << PD5);
		
	}
	else if(receiverbuffer == 'X')
	{
		H_flag = 1;
		
	}
	else if(receiverbuffer == 'x')
	{
		H_flag = 0;
		
	}
		
	
}
ISR(USART_UDRE_vect)
{
	UDR0 = transmitterbuffer;
	
	UCSR0B &= ~(1U << UDRIE0);
	
	
}

