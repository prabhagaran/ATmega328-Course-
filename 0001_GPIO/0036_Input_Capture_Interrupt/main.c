/*
 * 0036_Input_Capture_Interrupt.c
 *
 * Created: 10-10-2023 11:32:18 AM
 * Author : vingyan
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



int main(void)
{
    DDRB |=  (1U << PB5); //Configure LED pin as output
	DDRB &= ~(1U << PB0); //Configure Input Capture pin as input
	PORTB |= (1U << PB0); //Active the Input Capture pin as Internal Pullup
	
	//Timer 1 config : no noise canceler , rising edge , normal mode,no presacaler 
	TCCR1A = 0x00;
	TCCR1B |= (1U << ICES1) | (1U << CS10);
	TCCR1C = 0x00;
	TIMSK1 |= (1U << ICIE1);
	sei();
    while (1) {}
	return 0;
}
ISR(TIMER1_CAPT_vect){
	TCNT1 = 0;
	PORTB |= (1U << PB5);
	_delay_ms(1000);
	PORTB &= ~(1U << PB5);	
}

