/*
 * menuselections.c
 *
 * Created: 10.11.2019 10:41:21
 *  Author: juliessk
 */ 
#include "menuselections.h"
	
can_message cali;
char pointarray[4] = "";
char name[5] = "aaaaa";

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
				if(game.mypoints > score(gethighscore())){
					char* testing = Chosename();
					testing[3] = pointarray[0];
					testing[4] = pointarray[1];
					sethighscore(testing);
					sendReset();
					return Highscore;
				}
			}
		break;
		case Multiplayer:
			oled_reset();
			oled_printf("Opponents score :");
			oled_pos(1,0);
			pointarray[0] = (game.enemypoints%100-game.enemypoints%10)/10 + '0';
			pointarray[1] = game.enemypoints%10 + '0';
			oled_printf(pointarray);
		break;
		
		case Highscore:
			oled_reset();
			oled_printf("----------------");
			oled_pos(1,0);
			oled_printf("HIGHSCORES: ");
			oled_pos(2,0);
			oled_printf("----------------");
			oled_pos(4,0);
			char toscreen[5];
			char* hold = gethighscore();
			for(int i = 0; i < 5 ; i++){
				toscreen[i] = hold[i];
			}
			oled_printf(toscreen);
		break;
		case Easy:
			sendDificulty(Easy);
			oled_reset();
			oled_printf("EASY IT IS!!");
		break;
		case Medium:
			sendDificulty(Medium);
			oled_reset();
			oled_printf("Medium IT IS!!");
		break;
		case Hard:
			sendDificulty(Hard);
			oled_reset();
			oled_printf("Hard IT IS!!");
		break;
	}
	return choice;
}
					//oled_printf("NEW HIGHSCORE!!");
					//oled_pos(4,0);
					//oled_printf(pointarray);