/*
 * 0018_USART_RX_INTERRUPT.c
 *
 * Created: 07-09-2023 01:04:57 PM
 * Author : vingyan
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


uint8_t receiverbuffer;

void uartInit(uint32_t baudRate)
{
	uint16_t ubrr = (F_CPU / ( 16 * baudRate)) - 1;
	
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	//set data frame
	
	UCSR0C = (1U << UCSZ01) | (1 << UCSZ00);
	//Enable Receiver and Transmitter
	UCSR0B = (1U << TXEN0) | (1U << RXEN0);
	
	sei();
}

int main(void)
{
    /* Replace with your application code */
	DDRB |= (1U << PB5);
	DDRB |= (1U << PB4);
	uartInit(9600);
	UCSR0B |= (1U << RXCIE0);
	
    while (1) 
    {
		PORTB |= (1U << PB4);
		_delay_ms(500);
		PORTB &= ~(1U << PB4);
		_delay_ms(500);
    }
	return 0;
}

ISR(USART_RX_vect)
{
	receiverbuffer = UDR0;

	if(receiverbuffer == '1')
	{
		
		PORTB |= (1U << PB5);
	}
	else if(receiverbuffer == '0')
	{
		
		PORTB &= ~(1U << PB5);
	}
		
}

