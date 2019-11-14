/*
 * ADC_driver.c
 *
 * Created: 19.09.2019 10:49:45
 *  Author: juliessk
 */ 


#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "bit_macros.h"
#include "ADC_driver.h"

#ifndef ADC_ADDRESS
#define ADC_ADDRESS 0x1400
#endif

volatile char* ext_adc = ADC_ADDRESS;
volatile char ADC_data;

ISR(INT1_vect){
	
	ADC_data = ext_adc[0x00];
}

void ADC_init(void){
	

	clear_bit(DDRD, PD3);
	set_bit(PORTD, PD3);	
	
	cli();
	
	set_bit(MCUCR, ISC11);
	clear_bit(MCUCR, ISC10);
	
	set_bit(GICR,INT1);

	sei();
}

char get_ADC_data(void){
	return ext_adc[0x00]; 
}

void ADC_start_read(ADC_channel channel){
	
	char data = 0x00;
	switch (channel) {
		case CHANNEL1 :
		data = 0x04;
		break;
		case CHANNEL2 :
		data = 0x05;
		break;
		case CHANNEL3 :
		data = 0x06;
		break;
		case CHANNEL4 :
		data = 0x07;
		break;
		default:
		printf("Not valid channel");
	}
	
	ext_adc[0] = data;
	
}
