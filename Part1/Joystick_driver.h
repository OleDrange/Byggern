/*
 * Joystic_driver.h
 *
 * Created: 12.09.2019 17:25:50
 *  Author: oledr
 */ 

#ifndef JOYSTICK_DRIVER_H_
#define JOYSTICK_DRIVER_H_


#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

typedef enum {
	LEFT, 
	RIGHT, 
	UP, 
	DOWN, 
	NEUTRAL
} JoystickDir;

typedef struct{
	int xPos;
	int yPos;
	JoystickDir Dir;
	
}Joystick;



void Joystick_calibrate(void);
Joystick joystickPos(void);
Joystick JoystickDirection(void);

#endif /* JOYSTICK_DRIVER_H_ */