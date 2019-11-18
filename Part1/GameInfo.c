/*
 * Game.c
 *
 * Created: 09.11.2019 11:15:14
 *  Author: juliessk
 */ 

#include "GameInfo.h"
gamevars game = {.enemypoints = 0,.mypoints=0};
can_message newmessage;
int sendinfoFlag =0;

void sendInfo(menu_option lastOption){
	slider_str slider = slider_position();
	
	Joystick minJoystick = joystickPos();
	printf("SEND INFO\r\n");
	can_message canMessage;
	canMessage.id = 1;
	canMessage.data[0] = slider.L;
	canMessage.data[1] = slider.R;
	canMessage.data[2] = slider_left_button();
	canMessage.data[3] = slider_right_button();
	canMessage.data[4] = lastOption;
	if(minJoystick.Dir == LEFT){
		canMessage.data[5] = 'R';
		canMessage.length = 6;
	}
	else
	{
		canMessage.length = 5;
	}
	can_message_send(&canMessage);
	
}
void sendReset(){
	can_message canMessage;
	canMessage.id = 2;
	canMessage.data[0] = 1;
	canMessage.length = 1;
	can_message_send(&canMessage);
}
void sendDificulty(menu_option diff){
	can_message canMessage;
	canMessage.id = 3;
	if(diff == Easy){
		canMessage.data[0] = 0;
	}
	else if (diff == Medium){
		canMessage.data[0] = 1;
	}
	else{
		canMessage.data[0] = 2;
	}
	canMessage.length = 1;
	can_message_send(&canMessage);
}
gamevars getInfo(){
	if(can_interrupt()){
		newmessage = can_handle_messages();
		game.enemypoints = newmessage.data[0];
		game.mypoints = newmessage.data[1];
		
		//printf("MY POINTS    %d \r\n",game.mypoints);
		//printf("ENEMYPOINTS    %d  ",game.enemypoints);
		}
		
	
	return game;
}