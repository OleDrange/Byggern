/*
 * oled_menu.c
 *
 * Created: 26.09.2019 10:20:04
 *  Author: juliessk
 */ 

#include "oled_driver.h"
#include "oled_menu.h"


volatile menu* current_menu;
volatile int current_line = 2;
volatile int current_menu_size;

void set_right_sibling(menu* mymenu, menu* right_sibling) {
	mymenu->right_sibling = right_sibling;
}


void set_first_child(menu* mymenu, menu* first_child) {
	mymenu->first_child = first_child;
}


menu* new_menu(char* name, menu* parent) {
	menu* nextmenu = malloc(sizeof(menu));
 	nextmenu->title = name;
	nextmenu->parent = parent;
 	nextmenu->right_sibling = NULL;
	nextmenu->first_child = NULL;
	return nextmenu;
}

int size_of_menu(menu* mymenu) {
	
	int menu_size = 0;
	
	mymenu = mymenu->first_child;
	if (mymenu == NULL) {
		return menu_size;
	}
	menu_size ++;
	while (mymenu->right_sibling != NULL) {
		mymenu = mymenu->right_sibling;
		menu_size++;
	}
	return menu_size;
}

menu* oled_menu_init(void) {
	menu* main_menu = new_menu("Main Menu", NULL);
	menu* play_game = new_menu("Play Game", main_menu);
	menu* highscores = new_menu("Highscores", main_menu);
	menu* Test = new_menu("Test", main_menu);
	menu* Test1 = new_menu("Test1", Test);
	menu* Test2 = new_menu("Test2", Test1);
	menu* TestP = new_menu("TestP", play_game);
	menu* TestH = new_menu("TestH", highscores);
	
	
	current_menu = main_menu;
	current_menu_size = size_of_menu(current_menu);
	oled_menu_print(current_menu);

	set_first_child(main_menu, play_game);
	set_right_sibling(play_game, highscores);
	set_right_sibling(highscores,Test);
	//set_right_sibling(Test,Test1);
	set_first_child(Test, Test1);
	set_first_child(play_game, TestP);
	set_first_child(highscores, TestH);
	//set_right_sibling(Test1,Test2);
	set_first_child(Test1, Test2);
	return current_menu;
}


JoystickDir oled_menu_select(void){
	JoystickDir direction = JoystickDirection().Dir;
	current_menu_size = size_of_menu(current_menu);
	if(direction == UP){
		current_line--;
	}
	if(direction == DOWN){
		current_line++;
	}
	if(current_line > current_menu_size-1){
		current_line = current_menu_size-1;
	}
	if(current_line < 0){
		current_line = 0;
	}
	if(direction == RIGHT){
		if(current_menu->first_child != NULL){
				current_menu = current_menu->first_child;
		}
		for(int i =0; i < current_line;i++){
			current_menu = current_menu->right_sibling;
		}
		current_line = 0;
	}
	if(direction == LEFT){
		if(current_menu->parent != NULL){
		current_menu = current_menu->parent;
		}
	}
	current_menu_size = size_of_menu(current_menu);
	oled_menu_print(current_menu);
	return direction;
}

void oled_menu_print(menu* mymenu){
	
	oled_reset(); 
	
	current_menu_size = size_of_menu(mymenu);
	mymenu = mymenu->first_child;
	for(int i = 0; i < current_menu_size; i++){
		oled_pos(i,0);
		if(current_line == i){
			oled_inv_printf(mymenu->title);
		}
		else{
			oled_printf(mymenu->title);
		}
		mymenu = mymenu->right_sibling;
	}
	mymenu = mymenu->parent;
	
}