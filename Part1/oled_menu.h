/*
 * oled_menu.h
 *
 * Created: 26.09.2019 10:20:29
 *  Author: juliessk
 */ 

#ifndef OLED_MENU
#define OLED_MENU

#include "Joystick_driver.h"
#include "oled_driver.h"
typedef enum{
	NONE,
	SinglePlayer,
	Multiplayer,
	Highscore,
	Settings,
	Difficulty,
	Testing,
	Easy,
	Medium,
	Hard
} menu_option;

typedef struct{
	char* title;
	menu_option option;
	struct menu* parent;
	struct menu* first_child;
	struct menu* right_sibling;

	} menu;
	

menu_option oled_menu_select(); 
menu* oled_menu_init(void); 
void oled_menu_print(menu*);
void singleplayer(int);
void showHighscore();

#endif OLED_MENU