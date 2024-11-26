#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

#define TRIG_PIN    PB0
#define ECHO_PIN    PB1

void ultrasonic_init() {
	// Set TRIG_PIN as output
	DDRB |= (1 << TRIG_PIN);
	
	// Set ECHO_PIN as input
	DDRB &= ~(1 << ECHO_PIN);
}

uint16_t ultrasonic_get_distance() {
	// Send a 10us pulse on TRIG_PIN
	PORTB |= (1 << TRIG_PIN);
	_delay_us(10);
	PORTB &= ~(1 << TRIG_PIN);
	
	// Wait for the pulse to start
	while (!(PINB & (1 << ECHO_PIN)));
	
	// Measure pulse duration on ECHO_PIN
	uint16_t count = 0;
	while (PINB & (1 << ECHO_PIN)) {
		count++;
		_delay_us(1); // Adjust the delay based on your needs and system clock
	}

	// Calculate distance in centimeters
	return (uint16_t)(count / 2) *0.0343;
}

int main(void) {
	ultrasonic_init();
	Serial_begin(9600);
	
	while (1) {
		// Get distance from ultrasonic sensor
		uint16_t distance = ultrasonic_get_distance();
		
		// Your code to process distance data (e.g., display, control, etc.)
		SerialPrintf("Distance = %d\r\n",distance);
		// Add a delay between readings
		_delay_ms(500);
	}

	return 0;
}