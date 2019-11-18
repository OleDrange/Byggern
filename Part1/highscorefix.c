/*
 * highscorefix.c
 *
 * Created: 18.11.2019 13:02:38
 *  Author: oledr
 */ 

#include "highscorefix.h"
long slider=0;
long letter = 0;
long lastletter = 100;
int chosenLetters = 0;
int sliderbuttonhold = 0;
char newname[5] = "";
int havehighscore = 0;
void initHighscore(){
		sethighscore("12300");
}
char* gethighscore(){
	if(!havehighscore){
		return "NOSCORE";
	}
	char hold[5];
	for(int i = 3 ; i < 8 ; i++){
		hold[i-3] = SRAM_read(i);
	}
	return hold;
}
void sethighscore(char* array){
	havehighscore = 1;
	for(int i = 3; i < 8 ; i++){
		SRAM_write(i,array[i-3]);
	}
}

int score(char*array){
	int num = (int)array[3]-48;
	num *= 10;
	num += (int)array[4]-48;
	return num;
}

long maplols(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
char* Chosename(){
	while(chosenLetters < 3){
		slider = slider_position().R;
		letter = maplols(slider,0,255,65,90);
		newname[chosenLetters] = (char)letter;
		if(lastletter != letter){
			oled_reset();
			oled_printf("New highscore!");
			oled_pos(1,0);
			oled_printf("Select your name");
			oled_pos(2,0);
			oled_printf("with slider:");
			oled_pos(3,0);
			oled_printf(newname);
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
	chosenLetters = 0;
	return newname;
}