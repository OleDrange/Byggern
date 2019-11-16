/*
 * menuselections.h
 *
 * Created: 10.11.2019 10:45:52
 *  Author: juliessk
 */ 
#ifndef menuselection
#define menuselection

#include <avr/io.h>
#include <util/delay.h>
#include "oled_menu.h"
#include "CAN.h"
#include "GameInfo.h"
#include "slider.h"
#include "GameInfo.h"


menu_option printgame(menu_option,gamevars);
void EditHighscore(char*);


#endif menuselection