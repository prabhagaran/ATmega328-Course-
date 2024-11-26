#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

#define SS_PIN   PB2 // PB2 as Slave Select
#define MOSI_PIN PB3
#define MISO_PIN PB4
#define SCK_PIN  PB5

void SPI_MasterInit() {
	// Set MOSI, SCK, and SS as output
	DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN);

	// Enable SPI, set as master, and set clock rate (fosc/16)
	SPCR |= (1 << SPE) | (1 << MSTR) |(1 << DORD) | (1 << CPHA ) | (1 << SPR0);
}

uint8_t SPI_Transmit(uint8_t data) {
	// Load data into the buffer
	SPDR = data;

	// Wait for transmission complete
	while (!(SPSR & (1 << SPIF)));

	// Return received data
	return SPDR;
}

int main(void) {
	SPI_MasterInit();
	Serial_begin(9600);

	while (1) {
		// Send a byte to the slave
		char dataToSend = 'A';
		PORTB &= ~(1 << SS_PIN); // Activate the slave
		uint8_t receivedData = SPI_Transmit(dataToSend);
		PORTB |= (1 << SS_PIN);  // Deactivate the slave

		// Process the received data as needed
		// ...
		SerialPrintf("Received data = %c\r\n",receivedData);

		_delay_ms(1000);  // Adjust the delay based on your application requirements
	}

	return 0;
}
