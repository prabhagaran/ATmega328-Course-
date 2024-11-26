/*
 * Description: AVR code for USART communication using UART protocol with receive interrupt.
 *              This code initializes USART communication, sets up UART communication parameters,
 *              enables receive interrupt, and toggles an LED based on received characters.
 * Author: vingyan
 * Created: 07-09-2023 01:04:57 PM
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t receiverbuffer;

// Function to initialize UART communication with specified baud rate
void uartInit(uint32_t baudRate)
{
    uint16_t ubrr = (F_CPU / ( 16 * baudRate)) - 1;
    
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    
    // Set data frame
    UCSR0C = (1U << UCSZ01) | (1 << UCSZ00);
    
    // Enable Receiver and Transmitter
    UCSR0B = (1U << TXEN0) | (1U << RXEN0);
    
    sei(); // Enable global interrupts
}

int main(void)
{
    /* Replace with your application code */
    DDRB |= (1U << PB5); // Set PB5 as output for LED
    DDRB |= (1U << PB4); // Set PB4 as output for debugging
    
    uartInit(9600); // Initialize UART with baud rate of 9600
    
    UCSR0B |= (1U << RXCIE0); // Enable USART RX Complete Interrupt
    
    while (1) 
    {
        PORTB |= (1U << PB4); // Toggle PB4 for debugging
        _delay_ms(500);
        PORTB &= ~(1U << PB4);
        _delay_ms(500);
    }
    return 0;
}

// USART RX Complete Interrupt Service Routine
ISR(USART_RX_vect)
{
    receiverbuffer = UDR0; // Read received data
    
    UDR0 = receiverbuffer; // Echo back received data
    
    // Toggle LED based on received characters
    if (receiverbuffer == '1')
    {
        PORTB |= (1U << PB5); // Turn on LED
    }
    else if (receiverbuffer == '0')
    {
        PORTB &= ~(1U << PB5); // Turn off LED
    }
}
