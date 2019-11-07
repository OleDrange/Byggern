/*
 * PID.c
 *
 * Created: 07.11.2019 13:03:35
 *  Author: juliessk
 */ 


#include <avr/interrupt.h>
#include <avr/io.h>
#include "PID.h"

volatile int16_t pos;
volatile int16_t posd;


double timestep = 0.016;
double Kp = 0.1;
double Ki = 0.05;
double Kd = 0.004;

int16_t e;
double integral = 0;
double eprev = 0;
double deriv = 0;
int16_t speed;
volatile int count = 0;
ISR(TIMER2_OVF_vect){
	count++;
	if(count > 1){
	pos = motor_encoder(0);
	e = posd - pos;
	printf("posd: %d  ", posd);
	printf("pos: %d  ", pos);
	printf("e: %d  ", e);
	
	
	integral = integral + e*timestep;
	deriv = (e-eprev)/timestep;
	eprev = e;
	if(e < 2){
		integral = 0;
	}
	
	
	speed = Kp*e +  Kd * deriv + Ki * integral;
	printf("speed: %d  ", speed);
	uint8_t speedout;
	if(speed > 300){
		speed = 300;
		motor_set_direction(LEFT);
	}
	if(speed < -300){
		speed = -300;
		motor_set_direction(RIGHT);
	}
	if(speed < 0){
		speed = mapspeed(speed,-1,-300,0,80);
	}
	else{
		speed = mapspeed(speed,0,300,0,80);
	}
	printf("speed: %d   ", speed);
	speedout = speed;
	printf("speedout: %d  \r\n ", speedout);
	
	motor_set_speed(speedout);
	
	count = 0;
	}
	
}

void PID_init(){
	
	cli();
	
	// enable timer 2
	TIMSK2 = (1<<TOIE2);
	
	// start timer 2
	
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
	
	sei();
	
}

void PID_setpos(int16_t SETPUNKT){
	posd = SETPUNKT;
}
int16_t mapspeed(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}