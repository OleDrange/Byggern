/*
 * slider.c
 *
 * Created: 19.09.2019 14:04:38
 *  Author: juliessk
 */ 

#include "slider.h"
#include "ADC_driver.h"


SLI_pos_t slider_position(){
	SLI_pos_t sliderposition; 
	
	ADC_start_read(CHANNEL3);
	_delay_us(200);
	sliderposition.L = get_ADC_data();
	ADC_start_read(CHANNEL4);
	_delay_us(200);
	sliderposition.R =  get_ADC_data();
	
	return sliderposition;
}

//int slider_right_button(){
	//
	//return (PINB1);
//}
//
//int slider_left_button(){
	//
	//return (PINB2);
//}
