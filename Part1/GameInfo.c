/*
 * Game.c
 *
 * Created: 09.11.2019 11:15:14
 *  Author: juliessk
 */ 

#include "GameInfo.h"
void sendInfo(){
	slider_str slider = slider_position();
	
	Joystick minJoystick = joystickPos();
	
	can_message canMessage;
	canMessage.data[0] = slider.L;
	canMessage.data[1] = slider.R;
	canMessage.data[2] = slider_left_button();
	//canMessage.data[3] = map(IOBORDBUTTONR,-100,100,0,200);
	//canMessage.data[4] = map(minJoystick.xPos,-100,100,0,200);
	canMessage.length = 3;

	can_message_send(&canMessage);
	
}
