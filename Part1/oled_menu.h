/*
 * oled_menu.h
 *
 * Created: 26.09.2019 10:20:29
 *  Author: juliessk
 */ 

#ifndef OLED_MENU_H_
#define OLED_MENU_H_

#include "Joystick_driver.h"

typedef enum{
	NEW_GAME,
	SETTINGS,
	DIFFICULTY
} menu_option;

typedef struct{
	char* title;
	menu_option option;
	struct menu* parent;
	struct menu* first_child;
	struct menu* right_sibling;

	} menu;
	

JoystickDir oled_menu_select(void); 
menu* oled_menu_init(void); 
void oled_menu_print(menu*);

#endif OLED_MENU_H_