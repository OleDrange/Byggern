/*
 * PID.h
 *
 * Created: 07.11.2019 13:03:47
 *  Author: juliessk
 */ 

#include "motor_driver.h"
#include "DAC.h"

ISR(TIMER2_OVF_vect);
uint8_t PID_NewUpdate();
void PID_update();
void PID_setpos(int16_t SETPUNKT);
void PID_init();
long mapspeed(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max);