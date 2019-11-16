/*
 * Byggern.c
 *
 * Created: 19.09.2019 10:43:42
 *  Author: juliessk
 */ 


#include "DriverATmega162.h"
#include "SRAMTestProgram.h"
#include "ADC_driver.h"
#include "SRAM_driver.h"
#include "Joystick_driver.h"
#include "slider.h"
#include "oled_driver.h"
#include "oled_menu.h"
#include "CAN_controller_driver.h"
#include "CAN.h"
#include "GameInfo.h"
#include "menuselections.h"

int nextIndex = 0;
int joystickarray[10];
long map(long x, long in_min, long in_max, long out_min, long out_max);
JoystickDir joyupdatejoystickavrage(JoystickDir input);
int main( )
{
	My_serial_Init ( MYUBRR );
	_delay_ms(1000);
	ADC_init();
	Joystick_calibrate();
	oled_init();
	menu* mymenu = oled_menu_init();
	Joystick myjoystick;
	gamevars mygame;
	gamevars mygameold;
	menu_option lastOption;
	int updatescore = 0;
	oled_menu_select(0);
	can_init(MODE_NORMAL);
	printf("NEW START!!!!");
	int sendinfoflag =0;
	int gamemode = 0;

	JoystickDir myjoystickhold = NEUTRAL;
	while(1)
	{
		//printf("TESTINGS\r\n");
		mygame = getInfo();
		if(mygame.enemypoints != mygameold.enemypoints || mygame.mypoints != mygameold.mypoints){
			updatescore = 1;
		}
		else{
			updatescore = 0;
		}
		mygameold = mygame;
		myjoystick = joystickPos();
		if(myjoystick.Dir != myjoystickhold){
			if(joyupdatejoystickavrage(myjoystick.Dir) == LEFT){
				sendReset();
				lastOption = NONE;
				printf("SVART!!!!");
			}
			if(lastOption == SinglePlayer || lastOption == Multiplayer){
				gamemode = 1;
			}
			else{
				lastOption = printgame(oled_menu_select(),mygame);
				sendInfo(lastOption);
				gamemode = 0;
			}
		}
		myjoystickhold = myjoystick.Dir;
		if(gamemode){
			if(updatescore){
				lastOption = printgame(lastOption,mygame);
				printf("UPDATE SCORE\r\n");
			}
			sendinfoflag++;
			if(sendinfoflag > 20){
				sendInfo(lastOption);
				sendinfoflag = 0;
			}
		}
		_delay_ms(10);
	}
	
	return 1;
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
JoystickDir joyupdatejoystickavrage(JoystickDir input){
	joystickarray[nextIndex] = input;
	nextIndex ++;
	if(nextIndex > 9){
		nextIndex = 0;
	}
	int count = 0;
	for(int i = 0; i < 9; i++){
		if(joystickarray[i] == 0){
			count++;
		}
	}
	if(count > 2){
		return LEFT;
	}
	return NEUTRAL;
}