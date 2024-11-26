/*
 * uart.h
 *
 * Created: 07-08-2023 09:48:03 AM
 *  Author: vingyan
 */ 


#ifndef UART_H_
#define UART_H_
#define F_CPU 16000000
#include <avr/io.h>
#include<stdio.h>

void Serial_begin(uint32_t baud_rate);
void SerialWrite(uint8_t data);
uint8_t SerialRead();
void printString(const char *str);
void SerialPrintf(const char *format,...);

#endif /* UART_H_ */