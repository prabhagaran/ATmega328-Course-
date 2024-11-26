/*
 * Description: AVR code for USART communication using UART protocol with data register empty interrupt.
 *              This code initializes USART communication, sets up UART communication parameters,
 *              implements a function to transmit data using interrupt-driven approach, and toggles an LED.
 * Author: vingyan
 * Created: 07-09-2023 12:25:35 PM
 */ 

#include <avr/io.h>
#define F_CPU      16000000
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t usart_transmitBuffer;

// Function to initialize UART communication with specified baud rate
void uart_Init(uint32_t baudRate)
{
    uint16_t ubrr = (F_CPU / (16 * baudRate)) - 1;
    
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    
    /* Enable Transmitter and Receiver */
    UCSR0B = (1U << RXEN0) | (1U << TXEN0);
    
    /* Set Data frame */
    UCSR0C = (1U << UCSZ01) | (1U << UCSZ00);
    
    sei(); // Enable global interrupts
}

// Function to transmit data via UART using interrupt
void usart_TransmissionaInterrupt(uint8_t data)
{
    usart_transmitBuffer = data;
    UCSR0B |= (1U << UDRIE0); // Enable USART Data Register Empty Interrupt
}

int main(void)
{
    DDRB |= (1U << PB5); // Set PB5 as output for LED
    
    uart_Init(9600); // Initialize UART with baud rate of 9600
    uint8_t local_data = 'a';
    usart_TransmissionaInterrupt(local_data); // Transmit 'a' using interrupt
    
    while (1) 
    {
        // Toggle LED connected to PB5
        PORTB |= (1U << PB5);
        _delay_ms(500);
        PORTB &= ~(1U << PB5);
        _delay_ms(500);
    }
}

// USART Data Register Empty Interrupt Service Routine
ISR(USART_UDRE_vect)
{
    // Transmit data from buffer
    UDR0 = usart_transmitBuffer;
    
    // Disable USART Data Register Empty Interrupt
    UCSR0B &= ~(1U << UDRIE0);
}
