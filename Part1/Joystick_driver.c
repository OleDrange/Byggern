/*
 * Joystic.c
 *
 * Created: 12.09.2019 17:25:27
 *  Author: oledr
 */ 


#include "Joystick_driver.h"
#include "ADC_driver.h"

uint8_t center_x , center_y;

void Joystick_calibrate(void){
	
	ADC_start_read(CHANNEL1);
	_delay_us(200);
	center_x = get_ADC_data();
	ADC_start_read(CHANNEL2);
	_delay_us(200);
	center_y = get_ADC_data();
	 
}

Joystick joystickPos(void){
	//position;// = {.xPos =0,.yPos = 0,.Dir = NEUTRAL};
	uint8_t x, y; 
	Joystick position;
	position.xPos = 0;
	position.yPos = 0;
	
	ADC_start_read(CHANNEL1);
	_delay_us(200);
	x = get_ADC_data();
	
	if(x > center_x){
		position.xPos = 100 * (x - center_x) / (0xFF - center_x);
	} else if (x < center_x){
		position.xPos = 100 * (x - center_x) / (center_x - 0);
	} else {
		position.xPos = 0;
	}
	ADC_start_read(CHANNEL2);
	_delay_us(200);
	y = get_ADC_data();
	if(y > center_y){
		position.yPos = 100 * (y - center_y) / (0xFF - center_y);
		} else if (y < center_y){
		position.yPos = 100 * (y - center_y) / (center_y - 0);
		} else {
		position.yPos = 0;
	}
	
	return position; 
	
	
}

Joystick JoystickDirection(void){
	Joystick position;
	position.Dir = NEUTRAL;
	
	position = joystickPos(); 
	
	if(position.xPos < -50){
		position.Dir = LEFT; 
	} else if (position.xPos > 50){
		position.Dir = RIGHT;
	}
	
	if(position.yPos < -50){
		position.Dir = DOWN; 
	} else if (position.yPos > 50){
		position.Dir = UP; 
	}
	
	//if(position.xPos == 0 && position.yPos == 0){
		//position.Dir = NEUTRAL; 
	//}
	
	return position;
}
