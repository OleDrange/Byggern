/*
 * Game.c
 *
 * Created: 09.11.2019 11:15:14
 *  Author: juliessk
 */ 

#include "GameInfo.h"
gamevars game = {.enemypoints = 0,.mypoints=0};
can_message newmessage;

void sendInfo(){
	slider_str slider = slider_position();
	
	Joystick minJoystick = joystickPos();
	
	can_message canMessage;
	canMessage.data[0] = slider.L;
	canMessage.data[1] = slider.R;
	canMessage.data[2] = slider_left_button();
	if(minJoystick.Dir == LEFT){
		canMessage.data[3] = 'R';
		canMessage.length = 4;
	}
	else
	{
		canMessage.length = 3;
	}
	
	//canMessage.data[3] = map(IOBORDBUTTONR,-100,100,0,200);
	//canMessage.data[4] = map(minJoystick.xPos,-100,100,0,200);
	

	can_message_send(&canMessage);
	
}
gamevars getInfo(){
	if(can_interrupt()){
		newmessage = can_handle_messages();
		game.enemypoints = newmessage.data[0];
		game.mypoints = newmessage.data[1];
	}
	printf("ENEMYPOINTS    %d  ",game.enemypoints);
	printf("MY POINTS    %d \r\n",game.mypoints);
	
	return game;
}