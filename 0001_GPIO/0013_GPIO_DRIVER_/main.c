#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "uart.h"

#define BUTTON_PIN   PC0   // Define the pin where the button is connected
#define LED_PIN      PB5   // Define the pin where the LED is connected



int isButtonPressed(uint8_t pin) {
	// Check if the button is pressed (low)
	if (!digitalRead(pin)) {
		_delay_ms(10);  // Debounce delay
		return !digitalRead(pin);  // Check again after debouncing
	}
	return 0;
}

int main() {
	
	Serial_begin(9600);
	pinMode(A0,INPUT_PULLUP);
	pinMode(A1,INPUT_PULLUP);
	pinMode(A2,INPUT_PULLUP);
	
	pinMode(BUILTIN_LED,OUTPUT);
	int count = 0;
	int num[10] = {};
		
		int i = 0;

	while (1) {
		if (isButtonPressed(A0)) {
			// Toggle the LED
			PORTB ^= (1 << LED_PIN);
            count = (count + 1) % 10;
			// Wait for the button to be released
			while (isButtonPressed(A0));
		}
		
		if (isButtonPressed(A1)) {
			// Toggle the LED
			PORTB ^= (1 << LED_PIN);
			count = (count - 1 + 10) % 10;
			// Wait for the button to be released
			while (isButtonPressed(A1));
		}
		if (isButtonPressed(A2)) {
			// Toggle the LED
			PORTB ^= (1 << LED_PIN);
			num[i] = count;
			i++;
			while (isButtonPressed(A2));
		}
		SerialPrintf("Count = %d i = %d num = %d\r\n",count,i,num[i -1]);
		
		if(i > 9)
		{
			for(int j = 0 ; j < 10; j++)
			{
				SerialPrintf(" %d \r",num[j]);
				
			}
			_delay_ms(3000);
			i =0;
		}
		
	}

	return 0;
}
