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
int NewHighscore = 0;
char name[3] = "AAA";
int slider;
int chosenLetters = 0;
menu_option printgame(menu_option choice,gamevars game)
{
	//if(NewHighscore = 1){
		//oled_reset();
		//oled_printf("Select your name:");
		//oled_pos(1,0);
		//slider = slider_position().R;
		//char letter = (char)map(slider,0,255,32,50);
		//printf("LETTER = %d     ",letter);
		//oled_inv_printf(name);
		//if(slider_left_button()){
			//chosenLetters++;
			//printf("LEFT SLIDER BUTTON     ");
		//}
		//if(chosenLetters > 2){
			//NewHighscore = 0;
		//}
		//
		//return choice;
	//}
	switch(choice){ 
		case SinglePlayer:
			oled_reset();
			oled_printf("Your score :");
			oled_pos(1,0);
			pointarray[0] = (game.mypoints%100-game.mypoints%10)/10 + '0';
			pointarray[1] = game.mypoints%10 + '0';
			oled_printf(pointarray);
			if(game.enemypoints > 0)
			{	
				oled_pos(2,0);
				oled_printf("GAME OVER");
				oled_pos(3,0);
				if(game.mypoints > score(highscorelist[4])){
					oled_printf("NEW HIGHSCORE!!");
					oled_pos(4,0);
					oled_printf(pointarray);
					NewHighscore = 1;
				}
			}
		break;
		case Multiplayer:
			oled_reset();
			oled_printf("Opponents score :");
			oled_pos(1,0);
			pointarray[4] = "";
			pointarray[0] = (game.enemypoints%100-game.enemypoints%10)/10 + '0';
			pointarray[1] = game.enemypoints%10 + '0';
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
	int num = (int)array[3]-48;
	num *= 10;
	num += (int)array[4]-48;
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

