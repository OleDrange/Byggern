/*
 * IR.h
 *
 * Created: 24.10.2019 16:08:34
 *  Author: juliessk
 */ 


#ifndef IR_DRIVER
#define IR_DRIVER


void IR_init(void);

uint16_t IR_average_filter(void);
uint16_t IR_game_over(void);
uint8_t enemyScore(void);
void setEnemyScore(int score);

#endif 