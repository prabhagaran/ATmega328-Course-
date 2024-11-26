/*
 * Description: AVR code for receiving and printing strings over USART communication using UART protocol.
 *              This code initializes USART communication, sets up UART communication parameters,
 *              implements functions to transmit and receive data, and demonstrates receiving and printing strings.
 * Author: vingyan
 * Created: 05-09-2023 10:25:11 AM
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // Required for variable arguments functions

// Function to initialize UART communication with specified baud rate
void uart_init(uint32_t baud_rate)
{
    /* Calculate the baudrate */
    uint16_t ubrr = (F_CPU / (16 * baud_rate)) - 1;
    
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    
    /* Enable Transmitter and Receiver */
    UCSR0B = (1U << RXEN0) | (1U << TXEN0);
    
    /* Set data Frame: 8 bits, 1 stop bit */
    UCSR0C = (1U << UCSZ01) | (1U << UCSZ00);
}

// Function to transmit data via UART
void uartTX(uint8_t data)
{
    /* Wait until transmitter buffer is complete */
    while(!(UCSR0A & ( 1U << UDRE0))) {}
    UDR0 = data;
}

// Function to receive data via UART
uint8_t uartRX(void)
{
    /* Wait for data to be received */
    while(!(UCSR0A & (1U << RXC0))) {} 
    return UDR0;
}

// Function to print a string via UART
void printString(const char *str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        uartTX(str[i]);
    }
}

// Function to read a string from UART
void Read_String(char *buffer, uint8_t size)
{
    int i = 0;
    char receivedChar;
    
    while(1)
    {
        receivedChar = uartRX();
        
        if((receivedChar == '\n') || (receivedChar == '\r'))
        {
            buffer[i] = '\0';
            break;
        }
        else if(i < (size - 1))
        {
            buffer[i] = receivedChar;
            i++;
        }
    }
}

// Function to print formatted string via UART
void SerialPrint(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[64];
    
    vsprintf(buffer, format, args);
    
    printString(buffer);
    
    va_end(args);
}

int main(void)
{
    uart_init(9600); // Initialize UART with baud rate of 9600
    DDRB |= (1U << PB5); // Set PB5 as output for testing
    
    char receivedString[64];
    
    /* Replace with your application code */
    while (1) 
    {
        // Read string from UART
        Read_String(receivedString, sizeof(receivedString));
        
        // Print received string via UART
        SerialPrint(receivedString);
    }
}
