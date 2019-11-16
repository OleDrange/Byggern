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
char name[5] = "AAA00";
long slider=0;
long letter = 0;
long lastletter = 100;
int chosenLetters = 0;
int sliderbuttonhold = 0;
long maplols(long x, long in_min, long in_max, long out_min, long out_max);
int ChoseName();
menu_option printgame(menu_option choice,gamevars game)
{
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
					name[3] = pointarray[0];
					name[4] = pointarray[1];
					oled_printf("NEW HIGHSCORE!!");
					oled_pos(4,0);
					oled_printf(pointarray);
					_delay_ms(2000);
					int hold = 0;
					int test = ChoseName();
					chosenLetters = 0;
					//sendReset();
					return Highscore;
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

long maplols(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int ChoseName(){
	while(chosenLetters < 3){
		slider = slider_position().R;
		letter = maplols(slider,0,255,65,90);
		name[chosenLetters] = (char)letter;
		if(lastletter != letter){
			oled_reset();
			oled_printf("Select your name:");
			oled_pos(1,0);
			oled_printf(name);
		}
		lastletter = letter;
		int sliderbutton = 0;
		if(slider_left_button() > 0){
			sliderbutton = 1;
		}
		if(sliderbutton && sliderbutton != sliderbuttonhold){
			chosenLetters = chosenLetters + 1;
		}
		sliderbuttonhold = sliderbutton;
	}
	EditHighscore(name);
	return chosenLetters;
}