#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void uart_Init(uint32_t baud_rate)
{
	/*Calculate the baudrate*/
	uint16_t ubrr = (F_CPU / (16 * baud_rate)) - 1;
	
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	/*Enable Transmitter and Receiver*/
	UCSR0B = (1U << RXEN0) | (1U << TXEN0);
	
	/*Set data Frame 8bits 1 stop bits */
	UCSR0C = (1U << UCSZ01) |(1U << UCSZ00);
	//UCSR0B = (1U << UCSZ02);
	
}

void uart_Transmit_9bit(uint16_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)))
	;
	
	/* Copy 9th bit to TXB8 */
	UCSR0B &= ~(1 << TXB80);  // Clear TXB8 bit

	if (data & 0x0100)
	UCSR0B |= (1 << TXB80);  // Set TXB8 bit if the 9th bit of data is set

	/* Put data into buffer, sends the data */
	UDR0 = data;
}

int main(void) {
	// Initialize UART with a baud rate (e.g., 9600 bps)

	uart_Init(9600);

	while (1) {
		// Transmit a 9-bit data frame (0x1FF in this example)
		uart_Transmit_9bit(0x1FF);

		// Wait for a while
		_delay_ms(1000);
	}
	return 0;
}
