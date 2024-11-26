#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t timer_overflow_count = 0;

void setup_timer1_ctc() {
	// Set Timer1 in CTC mode with a prescaler of 64
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

	// Set the compare value for a specific delay (adjust this value for your specific requirements)
	OCR1A = 65503;  // For a delay of 1 second with a prescaler of 64

	// Enable Timer1 compare match A interrupt
	TIMSK1 |= (1 << OCIE1A);
}

int main(void) {
	setup_timer1_ctc();
	DDRB |= (1 << PB5);

	// Enable global interrupts
	sei();

	while (1) {
		// Your main code goes here

		
	}

	return 0;
}

// Timer1 compare match A interrupt service routine
ISR(TIMER1_COMPA_vect) {
	// Increment the overflow count
	timer_overflow_count++;
	PORTB ^= (1 <<PB5);
}
