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
int LeftButtonhold;
long setpunktmotor;
int servo;
int points = 0;
int Reset;
void PlayGame(){
	//printf("PLAY GAME ");
	DDRB |= (1<<PB6);
	if (can_interrupt()){
		
		canMessage = can_handle_messages();
		Slider_L = canMessage.data[0];   //printf("SLIDER_L = %d    ",Slider_L);
		Slider_R = canMessage.data[1];	 //printf("SLIDER_R = %d    ",Slider_R);
		LeftButton = canMessage.data[2]; //printf("LeftButton = %d   \r\n ",LeftButton);
		if(canMessage.data[3] == 'R'){
			Reset = 1;
			points = 0;
			setEnemyScore(0);
		}
		else
		{
			Reset = 0;
		}
		//printf("RESET  %d  \r\n", Reset);
		setpunktmotor = mapslider(Slider_R,0,255,-100,8300);
		PID_setpos(setpunktmotor);
		
		servo = mapslider(Slider_L,0,255,100,-100);
		
		set_servo(servo);
		//printf("leftbutton = %d     leftbuttonhold = %d  \r\n", LeftButton,LeftButtonhold);
		if((LeftButtonhold != LeftButton) && LeftButton){
			HitBall();
		}
	}
	if(PID_NewUpdate()){
		PID_update();
	}
	LeftButtonhold = LeftButton;
	_delay_ms(100);
}
void HitBall(){
	
	PORTB |= (1<<PB6);
	_delay_ms(1000);
	PORTB &= ~(1<<PB6);
	points++;
	//printf("POINTS = %d \r\n",points);
}

void SendInfo(){
	IR_game_over();
	can_message canMessageOut;
	canMessageOut.data[0] = enemyScore();
	canMessageOut.data[1] = points;
	canMessageOut.length = 2;
	canMessageOut.id = 1;
	can_message_send(&canMessageOut);
	printf("POINTSSEND = %d    ",points);
	printf("ENEMYPOINT = %d \r\n",enemyScore());
}

long mapslider(int x, int in_min, int in_max, int out_min, int out_max){
	return (long)(x - in_min) * (long)(out_max - out_min) / (long)(in_max - in_min) + out_min;
}
