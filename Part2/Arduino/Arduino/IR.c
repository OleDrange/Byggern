/*
 * IR.c
 *
 * Created: 24.10.2019 16:08:03
 *  Author: juliessk
 */ 
#include <AVR/io.h>
#include <stdbool.h>
#include "IR.h"
#include "ADC.h"

uint8_t num_readings = 4;
uint16_t readings[4];
uint8_t read_index = 0;
uint16_t total = 0;
static uint8_t enemys;
bool hasBeen0 = false;

void IR_init() {
	ADC_init();
	
	for (uint8_t this_reading = 0; this_reading < num_readings; this_reading++) {
		readings[this_reading] = 0;
	}
	
	readings[read_index] = ADC_read();
	total = readings[read_index];
	enemys = 0;
}

uint16_t IR_average_filter() {
	
	total = total - readings[read_index];
	
	readings[read_index] = ADC_read();
	
	total = total + readings[read_index];
	
	read_index = read_index + 1;
	
	if (read_index >= num_readings) {
		read_index = 0;
	}
	
	uint16_t average = total / num_readings;
	return average;
}

uint16_t IR_game_over() {
	if (IR_average_filter() < 200) {
		if(hasBeen0){
			enemys = enemys + 1;
			hasBeen0 = false;
		}
		
		return 1;
	}
	else {
		hasBeen0 = true;
		return 0;
		
	}
}
uint8_t enemyScore(){
	return enemys;
}