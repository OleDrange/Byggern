/*
 * SPI_driver.c
 *
 * Created: 03.10.2019 14:27:35
 *  Author: oledr
 */ 
#include <avr/io.h>

#include "bit_macros.h"
#include <avr/delay.h>
void SPI_init(){
	
	// Set SS, MOSI and SCK output
	DDRB = (1<<PB4)|(1<<PB5)|(1<<PB7);
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	/* Set SS-pin high */
	set_bit(PORTB, PB4);
	
}

void SPI_write(char cData) {
	
	
	/* Start transmission */
	SPDR = cData;
	
	/* Wait for transmission complete */
	loop_until_bit_is_set(SPSR, SPIF);
	
}

char SPI_read() {
	
	/* Start shifting registers by putting a char in the register */
	SPDR = 0x00;
	//_delay_ms(10);
	/* Wait for receive complete */ 
	loop_until_bit_is_set(SPSR,SPIF);
	
	return SPDR;
}
