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
double Ki = 0.1;
double Kd = 0.0009;
int16_t e;
int16_t abse;
double integral = 0;
double eprev = 0;
double deriv = 0;
int16_t speed;
int count = 0;
ISR(TIMER2_OVF_vect){
	flagpid = 1;
}
uint8_t PID_NewUpdate(){
	if (flagpid){	
		flagpid = 0;
		return 1;
	}
	return 0;
}

void PID_init(){
	
	cli();
	
	// enable timer 2
	TIMSK2 = (1<<TOIE2);
	
	// start timer 2
	
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
	
	sei();
	
}
void PID_update(){
	pos = motor_encoder(0);
	e = pos - posd;
	abse = abs(e);
	//printf("posd: %d  ", posd);
	//printf("pos: %d  ", pos);
	//printf("e: %d  ", e);
	
	
	integral = integral + e*timestep;
	deriv = (e-eprev)/timestep;
	eprev = e;
	if(e < 2){
		integral = 0;
	}
	
	
	speed = Kp*abse +  Kd * deriv + Ki * integral;
	if(e > 0) { motor_set_direction(RIGHT);}
		else {motor_set_direction(LEFT);}
		
	volatile uint8_t speedout;
	if(speed > 500){
		speed = 500;
	}
	if(speed < -500){
		speed = -500;
	}
	printf("Error = %d   ",e); printf("speed: %d   ", speed);
	speed = abs(speed);
	printf("speed: %d   ", speed);
	speed = (int16_t)mapspeed(speed,0,500,0,100);
	
	
	speedout = speed; printf("speedout: %d \r\n  ", speedout);
	
	motor_set_speed(speedout);
}

void PID_setpos(int16_t SETPUNKT){
	posd = SETPUNKT;
}
long mapspeed(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
	return (long)(x - in_min) * (long)(out_max - out_min) / (long)(in_max - in_min) + out_min;
}