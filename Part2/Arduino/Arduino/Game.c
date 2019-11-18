/*
 * Game.c
 *
 * Created: 27.10.2019 12:56:56
 *  Author: juliessk
 */ 
#include "Game.h"

can_message canMessage;
long Slider_L;
int Slider_R;
int LeftButton;
int RightButton;
int solonoidFlag;
long setpunktmotor;
int servo;
int points = 0;
int Reset;
int sendinfoFlag =0;
int menuOption = 0;
void PlayGame(){
	//printf("PLAY GAME ");
	DDRB |= (1<<PB6);
	if (can_interrupt()){
		
		canMessage = can_handle_messages();
		//printf("ID = %d \r\n",canMessage.id);
		if(canMessage.id == 1){
			Slider_L = canMessage.data[0];   
			Slider_R = canMessage.data[1];	 
			LeftButton = canMessage.data[2]; 
			RightButton = canMessage.data[3];
			menuOption = canMessage.data[4];
			if(RightButton){
				motor_calibrate();
			}
		}
		else if (canMessage.id == 3){
			if (canMessage.data[0] == 0)
			{
				PID_SET_EASY();
			}
			else if (canMessage.data[0] == 1)
			{
				PID_SET_MEDIUM();
			}
			else
			{
				PID_SET_HARD();
			}
			
		}
		if(canMessage.id == 2){
			Reset = 1;
			points = 0;
			setEnemyScore(0);
		}
		else
		{
			Reset = 0;
		}
	}
		if(menuOption == 1 || menuOption == 2 || menuOption == 4){
			setpunktmotor = mapslider(Slider_R,0,255,8600,-100);
			PID_start();
			PID_setpos(setpunktmotor);
					
			servo = mapslider(Slider_L,0,255,-100,100);
					
			set_servo(servo);
			if(!solonoidFlag && LeftButton){
				solonoidFlag = 1;
				HitBall();
				if(menuOption == 1 && enemyScore() == 0){
					points++;
				}
			}
			else{
				PID_stop();
			}
			if(!LeftButton){
				solonoidFlag = 0;
			}
		}

}
void HitBall(){
	
	PORTB |= (1<<PB6);
	_delay_ms(1000);
	PORTB &= ~(1<<PB6);
}

void SendInfo(){
	if(menuOption == 1 || menuOption == 2 || menuOption == 4 || Reset){
		sendinfoFlag++;
		if(sendinfoFlag > 500){ // to not overuse the canbuss
			IR_game_over();
			can_message canMessageOut;
			canMessageOut.data[0] = enemyScore();
			canMessageOut.data[1] = points;
			canMessageOut.length = 2;
			canMessageOut.id = 1;
			can_message_send(&canMessageOut);
			sendinfoFlag = 0;
		}
		
	}
}

long mapslider(int x, int in_min, int in_max, int out_min, int out_max){
	return (long)(x - in_min) * (long)(out_max - out_min) / (long)(in_max - in_min) + out_min;
}
