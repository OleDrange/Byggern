/*
 * menuselections.c
 *
 * Created: 10.11.2019 10:41:21
 *  Author: juliessk
 */ 
#include "menuselections.h"
char highscorelist[5][5] = {
	{'a', 'a', 'a', '0','0'} ,
	{'b', 'b', 'b', '0','0'} ,
	{'c', 'c', 'c', '0','0'} ,
	{'c', 'c', 'c', '0','0'},
	{'c', 'c', 'c', '0','0'} };
		
		
can_message cali;
char pointarray[4] = "";
menu_option printgame(menu_option choice,gamevars game)
{
	switch(choice){ 
		case SinglePlayer:
			oled_reset();
			oled_printf("Your score is :");
			oled_pos(1,0);
			pointarray[0] = (game.mypoints%100-game.mypoints%10)/10 + '0';
			pointarray[1] = game.mypoints%10 + '0';
			oled_printf(pointarray);
			if(game.enemypoints > 0)
			{	
				oled_pos(2,0);
				oled_printf("GAME OVER");
			}
			

		break;
		case Multiplayer:

			oled_reset();
			oled_printf("Your score is :");
			oled_pos(1,0);
			pointarray[4] = "";
			pointarray[0] = (game.mypoints%100-game.mypoints%10)/10 + '0';
			pointarray[1] = game.mypoints%10 + '0';
			oled_printf(pointarray);


		break;
		case Highscore:
		oled_reset();
		oled_printf("HIGHSCORES: ");
		for(int i = 0; i < 5; i++){
			oled_pos(i+1,0);
			char hold[6] = "";
			for(int j = 0; j < 5; j++){
				hold[j] = highscorelist[i][j];
			}
			oled_printf(hold);
		}
		break;
		case Calibrate:
			cali.id = 10;
			cali.data[0] = 0;
			cali.length = 1;
			can_message_send(&cali);
		break;
	}
	return choice;
}
void EditHighscore(char* array){
	for(int i = 0 ; i < 5;i++)
	{
		if(score(highscorelist[i]) < score(array)){
			highscorelistupdate(i,array);
			break;
		}
	}
}
int score(char*array){
	int num = (int)array[3];
	num *= 10;
	num += (int)array[4];
	return num;
}
void highscorelistupdate(int i,char*array){
	for(int j = i; j < 4; j++)
	{
		for(int z = 0; z < 5; z++){
			highscorelist[j+1][z] = highscorelist[j][z];
		}
		
	}
	for(int z = 0; z < 5; z++){
		highscorelist[i][z] = array[z];
	}
}