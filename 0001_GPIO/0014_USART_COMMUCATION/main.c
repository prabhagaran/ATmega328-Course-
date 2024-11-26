/*
 * Description: AVR code for USART communication using UART protocol.
 *              This code initializes USART communication, sets up UART communication parameters,
 *              and implements simple transmit and receive functions.
 *              Data received through USART is immediately transmitted back with carriage return ('\r')
 *              and line feed ('\n') characters appended.
 * Author: vingyan
 * Created: 05-09-2023 09:39:50 AM
 */ 

#define F_CPU 16000000UL // Define the clock frequency
#include <avr/io.h>
#include <util/delay.h>

// Function to initialize UART communication with specified baud rate
void uart_Init(uint32_t baud_rate)
{
    // Calculate the Baud Rate
    uint16_t ubrr = F_CPU / (16 * baud_rate) - 1;
    
    // Load the calculated USART Baud Rate Registers
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    
    // Set Data Frame: 8 bits, 1 stop bit, no parity
    UCSR0C = (1U << UCSZ01) | (1 << UCSZ00);
    
    // Enable the Transmitter and Receiver
    UCSR0B = (1U << TXEN0) | (1U << RXEN0);
}

// Function to transmit data via UART
void uart_transmit(uint8_t data)
{
    // Wait until the transmit buffer is empty
    while(!(UCSR0A & (1U << UDRE0))){}
    
    // Load the value into the data register
    UDR0 = data;
}

// Function to receive data via UART
uint8_t uart_receive(void)
{
    while(!(UCSR0A & (1U << RXC0))){}
    
    return UDR0;
}

int main(void)
{
    /* Replace with your application code */
    uart_Init(9600); // Initialize UART with baud rate of 9600
    uint8_t data;
    while (1) 
    {
        // Receive data from UART
        data = uart_receive();
        
        // Transmit received data back with carriage return ('\r') and line feed ('\n') characters
        uart_transmit(data);
        uart_transmit('\r');
        uart_transmit('\n');
        
        _delay_ms(1000); // Delay for 1 second
    }
}
