/*
 * File: 0006_GPIO_4_WAY_TRAFFIC_LIGHT.c
 * Author: vingyan
 * Description: This program controls a 4-way traffic light system using AVR microcontroller.
 * Notes:

	 This program controls a 4-way traffic light system using AVR microcontroller.
	 It defines pin mappings for each LED connected to the microcontroller's ports.
	 Functions all_led_on() and all_led_off() are used to turn on and off all LEDs, respectively.
	 The main loop controls the sequence of the traffic lights for each direction and implements delays using _delay_ms() function. Adjust the delay times as needed.
	 */ 

#define F_CPU 16000000 // Define CPU frequency for delay functions
#include <avr/io.h> // AVR Standard I/O Library
#include <util/delay.h> // Delay functions library

// Define pin mappings for each LED
#define N_RED_LED    PD4
#define N_YELLOW_LED PD3
#define N_GREEN_LED  PD2
#define S_RED_LED    PD7
#define S_YELLOW_LED PD6
#define S_GREEN_LED  PD5
#define E_RED_LED    PB2
#define E_YELLOW_LED PB1
#define E_GREEN_LED  PB0
#define W_RED_LED    PB5
#define W_YELLOW_LED PB4
#define W_GREEN_LED  PB3

// Function to turn off all LEDs
void all_led_off(void) {
    PORTD &= ~((1 << N_RED_LED) | (1 << N_YELLOW_LED) | (1 << N_GREEN_LED) | (1 << S_RED_LED) | (1 << S_YELLOW_LED) | (1 << S_GREEN_LED));
    PORTB &= ~((1 << E_RED_LED) | (1 << E_YELLOW_LED) | (1 << E_GREEN_LED) | (1 << W_RED_LED) | (1 << W_YELLOW_LED) | (1 << W_GREEN_LED));
}

// Function to turn on all LEDs
void all_led_on(void) {
    PORTD |= ((1 << N_RED_LED) | (1 << N_YELLOW_LED) | (1 << N_GREEN_LED) | (1 << S_RED_LED) | (1 << S_YELLOW_LED) | (1 << S_GREEN_LED));
    PORTB |= ((1 << E_RED_LED) | (1 << E_YELLOW_LED) | (1 << E_GREEN_LED) | (1 << W_RED_LED) | (1 << W_YELLOW_LED) | (1 << W_GREEN_LED));
}

int main(void) {
    // Set all LED pins as outputs
    DDRD |= (1 << N_RED_LED) | (1 << N_YELLOW_LED) | (1 << N_GREEN_LED) | (1 << S_RED_LED) | (1 << S_YELLOW_LED) | (1 << S_GREEN_LED);
    DDRB |= (1 << E_RED_LED) | (1 << E_YELLOW_LED) | (1 << E_GREEN_LED) | (1 << W_RED_LED) | (1 << W_YELLOW_LED) | (1 << W_GREEN_LED);
	
    while (1) {
        // North-South Green, East-West Red
        all_led_off();
        PORTB |= (1 << E_GREEN_LED);
        PORTB |= (1 << W_RED_LED);
        PORTD |= (1 << N_RED_LED);
        PORTD |= (1 << S_RED_LED);
        _delay_ms(3000);

        // North-South Yellow, East-West Red
        PORTB |= (1 << E_YELLOW_LED);
        PORTD |= (1 << N_YELLOW_LED);
        _delay_ms(2000);

        // North-South Red, East-West Green
        all_led_off();
        PORTD |= (1 << N_GREEN_LED);
        PORTD |= (1 << S_RED_LED);
        PORTB |= (1 << E_RED_LED);
        PORTB |= (1 << W_RED_LED);
        _delay_ms(3000);

        // North-South Yellow, East-West Red
        PORTB |= (1 << W_YELLOW_LED);
        PORTD |= (1 << N_YELLOW_LED);
        _delay_ms(2000);

        // North-South Red, East-West Green
        all_led_off();
        PORTB |= (1 << W_GREEN_LED);
        PORTB |= (1 << E_RED_LED);
        PORTD |= (1 << N_RED_LED);
        PORTD |= (1 << S_RED_LED);
        _delay_ms(3000);

        // North-South Yellow, East-West Red
        PORTB |= (1 << E_YELLOW_LED);
        PORTD |= (1 << S_YELLOW_LED);
        _delay_ms(2000);
    }
    return 0;
}
