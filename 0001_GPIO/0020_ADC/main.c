/*
 * File: 0020_ADC.c
 * Description: AVR code for reading analog sensor values using ADC and transmitting them via UART
 * Created: 15-09-2023 11:53:27 AM
 * Author: vingyan
 */ 

#define F_CPU 16000000 // Define CPU frequency for delay calculation
#include <avr/io.h>    // AVR Input/Output macros
#include <util/delay.h>// Delay functions
#include <stdio.h>     // Standard I/O functions
#include <stdlib.h>    // Standard library functions

// Function to initialize UART communication
void uartInit(uint32_t baudRate)
{
    // Calculate and set baud rate
	uint16_t ubrr = (F_CPU / (16 * baudRate)) - 1;
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	// Enable transmitter and receiver
	UCSR0B = (1U << RXEN0) | (1U << TXEN0);
	
	// Set data frame format: 8 data bits, 1 stop bit
	UCSR0C = (1U << UCSZ01) | (1U << UCSZ00);
}

// Function to initialize ADC
void adcInit()
{
	// Set reference voltage to AVCC (5V), left adjust ADC result
	ADMUX = (1U << REFS0);
	
	// Enable ADC, set ADC prescaler to 128
	ADCSRA = (1U << ADEN) | (1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0);
}

// Function to transmit a byte of data via UART
void transmittData(uint8_t data)
{
	// Wait until the transmit buffer is empty
	while(!(UCSR0A & (1U << UDRE0))) {}
	
	// Transmit data
	UDR0 = data;
}

// Function to read analog sensor value from specified channel
uint16_t analogRead(uint8_t channel)
{
	// Select ADC channel
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
	
	// Start conversion
	ADCSRA |= (1U << ADSC);
	
	// Wait for conversion to complete
	while(ADCSRA & (1U << ADSC)){}
	
	// Return ADC result
	return ADC;
}

// Function to transmit a string via UART
void printString(const char *str)
{
	// Loop through the string and transmit each character
	for(int i = 0; str[i] != '\0';i++)
	{
		transmittData(str[i]);
	}
}

// Function to print formatted data via UART
void SerialPrintf(const char *format,...)
{
	va_list args;
	va_start(args,format);
	char buffer[64];
	
	// Format data according to format string
	vsprintf(buffer,format,args);
	
	// Transmit formatted string
	printString(buffer);
	
	va_end(args);
}

int main(void)
{
    /* Replace with your application code */
	// Initialize UART communication and ADC
	uartInit(9600);
	adcInit();
	
	// Variable to store sensor value
	uint16_t sensorValue  =  20;
	
    while (1) 
    {
		// Read sensor value from ADC channel 0
		sensorValue = analogRead(0);
		
		// Transmit sensor value via UART
		SerialPrintf("The Sensor Value is = %d \r \n",sensorValue);
		
		// Delay for 1 second
		_delay_ms(1000);
    }
}
