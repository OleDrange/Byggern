/*
 * LatchTest.h
 *
 * Created: 05.09.2019 11:28:06
 *  Author: oledr
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

SetLatchBlink() {
	DDRC = 0x00;
	
	PORTA = 0xA4;
	_delay_ms(1000);
	PORTA = 0x00;
	_delay_ms(1000);
}
