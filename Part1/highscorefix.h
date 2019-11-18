/*
 * highscorefix.h
 *
 * Created: 18.11.2019 13:07:39
 *  Author: oledr
 */ 

#ifndef HIGHSCOREFIX
#define HIGHSCOREFIX
#include <avr/io.h>
#include <util/delay.h>
#include "SRAM_driver.h"
#include "slider.h"
#include "GameInfo.h"

long maplols(long x, long in_min, long in_max, long out_min, long out_max);
char* Chosename();
void EditHighscore(char*);
char* gethighscore();//uint16_t place);
void sethighscore(char* array);//uint16_t place,char* array);
//
//void setHighscore(char* name);
//char* getHighscore();

#endif 