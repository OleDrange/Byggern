/*
 * Motor_controll.c
 *
 * Created: 31.10.2019 13:23:32
 *  Author: juliessk
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "bit_macros.h"
#include "motor_driver.h"
#include "ADC.h"

void motor_init(){
	
	// Enable motor
	set_bit(DDRH, PH4);
	set_bit(PORTH, PH4);
	
	// Set direction pin to output
	set_bit(DDRH, PH1);
	
	//--------------------Set encoder pins to output and input mode----------------------
	
	// Output Enable pin (active low): !OE
	set_bit(DDRH, PH5);
	
	//Selection pin: SEL
	set_bit(DDRH, PH3);
	
	// Set Reset pin: RST
	set_bit(DDRH, PH6);
	// Reset encoder
	motor_reset_encoder();
	
	// Set data bits to input:
	clear_bit(DDRK, PK0);
	clear_bit(DDRK, PK1);
	clear_bit(DDRK, PK2);
	clear_bit(DDRK, PK3);
	clear_bit(DDRK, PK4);
	clear_bit(DDRK, PK5);
	clear_bit(DDRK, PK6);
	clear_bit(DDRK, PK7);
	
	motor_calibrate();
}

void motor_reset_encoder() {
	clear_bit(PORTH, PH6);
	_delay_us(200);
	set_bit(PORTH, PH6);
}


void motor_set_direction(motor_direction_t direction){
	switch (direction){
		case(LEFT):
			clear_bit(PORTH, PH1);
			break;
		case(RIGHT):
			set_bit(PORTH, PH1);
			break;
	}
}

void motor_set_speed(uint8_t speed){
	DAC_send(speed);
}

int16_t motor_encoder(uint8_t reset_flag){
	
	clear_bit(PORTH, PH5);
	
	//Set SEL high to get low byte
	set_bit(PORTH, PH3);
	
	_delay_us(60);
	
	//Read LSB
	uint8_t low = PINK;
	
	//Set SEL low to get high byte
	clear_bit(PORTH, PH3);
	
	_delay_us(60);
	
	//Read MSB
	uint8_t high = PINK;
	if (reset_flag) {
		motor_reset_encoder();
	}
	//Set !OE high to disable output of encoder
	set_bit(PORTH, PH5);
	
	int16_t rot = (int16_t) ( (high << 8) | low);
	
	return rot;
}

void motor_calibrate() {
	motor_set_direction(RIGHT);
	motor_set_speed(70);
	int16_t cur_rot = motor_encoder(0);
	int16_t prev_rot = cur_rot+200;
	while(prev_rot != cur_rot) {
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = motor_encoder(0);
	}
	motor_reset_encoder();
	motor_set_speed(0);
}
