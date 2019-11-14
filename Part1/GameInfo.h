/*
 * Game.h
 *
 * Created: 09.11.2019 11:15:52
 *  Author: juliessk
 */ 
#include "Joystick_driver.h"
#include "slider.h"
#include "oled_menu.h"
#include "CAN.h"

#ifndef GAMEINFO_H
#define GAMEINFO_H

typedef struct {
	int mypoints;
	int enemypoints;
} gamevars ;
void sendInfo(menu_option);
gamevars getInfo();

#endif GAMEINFO_H