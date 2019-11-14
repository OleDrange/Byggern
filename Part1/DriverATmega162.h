/*
 * DriverATmega162.h
 *
 * Created: 05.09.2019 10:20:10
 *  Author: oledr
 */ 

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define F_CPU 4915200UL


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <util/setbaud.h>

void My_serial_Init( unsigned int ubrr );
void My_serial_Transmit( unsigned char data );
unsigned char My_serial_Receive( void );


