/*
 * Game.h
 *
 * Created: 09.11.2019 12:20:03
 *  Author: juliessk
 */ 

#ifndef GAME
#define GAME

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "CAN.h"
#include "PID.h"
#include "PWM_servo_driver.h"

void PlayGame();
long mapslider(int x, int in_min, int in_max, int out_min, int out_max);
#endif GAME
