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



void My_serial_Init( unsigned int ubrr )
{
	
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	fdevopen(My_serial_Transmit, My_serial_Receive);
	

}

void My_serial_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char My_serial_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}