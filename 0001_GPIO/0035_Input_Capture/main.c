

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define LED (1<<PB5)

int main()
{
	DDRB |= LED;	//configure LED pin as output
	DDRB &= ~(1<<PB0);	//configure input capture pin as input
	PORTB |= (1<<PB0);	//activate input capture pin internal pullup

	//Timer 1 config: no noise canceller, rising edge, normal mode, no prescalar
	TCCR1A = 0x00;		//COM1A1 COM1A0 COM1B1 COM1B0 – – WGM11 WGM10
	TCCR1B |= (1U << ICES1) | (1U << CS10);                                      //0b01000001;	//ICNC1 ICES1 – WGM13 WGM12 CS12 CS11 CS10
	TCCR1C = 0x00;	//FOC1A FOC1B – – – – – –

	while (1){
		while((TIFR1 & (1<<ICF1)) == 0);	//poll the ICF1 bit
		TIFR1 |= (1<<ICF1);	//clear the ICF1
		PORTB |= LED; 	//turn on LED on event
		_delay_ms(1000);	//LED on for 1 sec
		PORTB &= ~LED;	//turn off LED	after 1sec
		
	}
	return 0;
}