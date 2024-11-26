/*
 * 0021_8bit_Timers.c
 *
 * Created: 19-09-2023 11:32:36 AM
 * Author : vingyan
 
 https://www.ee-diary.com/2021/07/atmega328p-fast-pwm-mode-programming.html
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void Timer0(void);  //function prototype

int main()
{
	
	DDRB |= (1<<PB5);    //for LED output
	
	while (1){
		PORTB ^= (1<<PB5);    //toggle PORT B pin 0
		Timer0();
	}
	return 0;
}

void Timer0(void){
	TCNT0 = 50;    //load the TCNT0 with 206 for 50us delay

	//for normal mode operation and pre-scalar of 8
	TCCR0A = 0x00;
	TCCR0B =  (1U << CS02) | (1U << CS00); // FOC0A | FOC0B | - | - | WGM02 | CS02 | CS01 | CS00
	
	while((TIFR0 & (1<<TOV0)) == 0);
	TCCR0B = 0x00;
	TIFR0 |= (1U << TOV0);
}

