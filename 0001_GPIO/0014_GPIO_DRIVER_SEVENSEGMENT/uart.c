#include"uart.h"


void Serial_begin(uint32_t baud_rate)
{
	// Calculate the UBRR value based on the desired baud rate and MCU's clock frequency
	uint16_t ubrr = F_CPU /(16 * baud_rate) - 1;
	// set baud rate registers 
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	//Set frame format: 8bits, no parity, 1 stop bits 
	UCSR0C = (1U << UCSZ01) | (1U << UCSZ00);
	//Enable Transmitter and receiver 
	UCSR0B = (1U << TXEN0) | (1U << RXEN0);
}

void SerialWrite(uint8_t data)
{
	
	//wait till transmitter buffer is empty
	while(!(UCSR0A &(1U << UDRE0))){}
   //Send the data to the UART data registers 
    UDR0 =  data;
}

uint8_t SerialRead()
{
	//wait for data to be received
	while(!(UCSR0A & (1U << RXC0))){}
    return UDR0;
}

void printString(const char *str)
{
	for(uint8_t i = 0; str[i] != '\0'; i++)
	{
		
		SerialWrite(str[i]);
	}
}

void SerialPrintf(const char *format, ...)
{  
	// Custom printf function supporting %d, %s, %c, and %f format specifier
	va_list args;
	va_start(args, format);
	
	char buffer[64];
	 // Use the standard C library sprintf() to handle formatting floating-point numbers
	vsprintf(buffer, format, args);
	
	printString(buffer);
	va_end(args);
}
