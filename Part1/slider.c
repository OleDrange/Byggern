/*
 * slider.c
 *
 * Created: 19.09.2019 14:04:38
 *  Author: juliessk
 */ 
#include "slider.h"


slider_str slider_position(void){
	slider_str sliderposition;
	ADC_start_read(CHANNEL3);
	_delay_us(200);
	sliderposition.L = get_ADC_data();
	ADC_start_read(CHANNEL4);
	_delay_us(200);
	sliderposition.R =  get_ADC_data();
	
	return sliderposition;
}

int slider_right_button(void){
	if((PINB & 0b00000010) != 0){ //PB1
		return 1;
	}
	return 0;
}

int slider_left_button(void){
	if((PINB & 0b00000100) != 0){ //PB2
		return 1;
	}
	return 0;
}

