/*
 * PWM_servo_driver.c
 *
 * Created: 24.10.2019 13:21:47
 *  Author: juliessk
 */ 

#include "PWM_servo_driver.h"
#include "PWM_driver.h"
#include <avr/io.h>

void servo_init(unsigned long clock_speed){
	
	float period_sec = 0.02;
	PWM_init(period_sec, clock_speed);
	PWM_pulse_set(0.0015);
	
}
void set_servo(int servo_dir){
	
	float min_pw = 0.0009;
	float max_pw = 0.0021;
	
	float dir = (float)servo_dir;
	
	float servo_pw = dir/200000.0 + 0.0015;
	
	if (servo_pw < min_pw) {
		servo_pw = min_pw;
	}
	if (servo_pw > max_pw) {
		servo_pw = max_pw;
	}
	PWM_pulse_set(servo_pw);
	
}