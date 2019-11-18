/*
 * PID.c
 *
 * Created: 07.11.2019 13:03:35
 *  Author: juliessk
 */ 

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include "PID.h"

int16_t pos;
int16_t posd;

volatile int flagpid = 0;

double timestep = 0.016;
double Kp = 0.08;
double Ki = 0.2;
double Kd = 0.0009;
int16_t e;
int16_t abse;
double integral = 0;
double eprev = 0;
double deriv = 0;
int16_t speed;
int count = 0;
int16_t topspeed = 80;
ISR(TIMER2_OVF_vect){
	pos = motor_encoder(0);
	e = pos - posd;
	abse = abs(e);
	integral = integral + e*timestep;
	deriv = (e-eprev)/timestep;
	eprev = e;
	if(e < 2){
		integral = 0;
	}
	speed = Kp*abse +  Kd * deriv + Ki * integral;
	if(e > 0) { motor_set_direction(RIGHT);}
	else {motor_set_direction(LEFT);}
	uint8_t speedout;
	if(speed > 500){
		speed = 500;
	}
	if(speed < -500){
		speed = -500;
	}
	if (abs(e) > 1800){
		speed = (int16_t)mapspeed(speed,0,500,40,topspeed+20);
	}
	else
	{
		speed = (int16_t)mapspeed(speed,0,500,38,topspeed);
	}
	speed = abs(speed);
	speedout = speed;
	motor_set_speed(speedout);
}

void PID_init(){
	
	cli();
	// enable timer 2
	TIMSK2 = (1<<TOIE2);
	
	sei();
	
}
void PID_start(){
	//Start timer 2
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
}
void PID_stop(){
	//Stop timer 2
	TCCR2B = 0;
}

void PID_setpos(int16_t SETPUNKT){
	posd = SETPUNKT;
}

void PID_SET_EASY(){
	//Kp = 0.08;
	//Ki = 0.2;
	//Kd = 0.0009;
	//printf("TEST EASY");
	topspeed = 120;
}
void PID_SET_MEDIUM(){
	//Kp = 0.1;
	//Ki = 0.25;
	//Kd = 0.0009;
	//printf("TEST MEDIUM");
	topspeed = 80;
}
void PID_SET_HARD(){
	//Kp = 0.15;
	//Ki = 0.5;
	//Kd = 0.00009;
	//printf("TEST HARD");
	topspeed = 170;
}


long mapspeed(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
	return (long)(x - in_min) * (long)(out_max - out_min) / (long)(in_max - in_min) + out_min;
}