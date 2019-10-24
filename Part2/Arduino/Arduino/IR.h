/*
 * IR.h
 *
 * Created: 24.10.2019 16:08:34
 *  Author: juliessk
 */ 


#ifndef IR_DRIVER_H_
#define IR_DRIVER_H_


void IR_init(void);

uint16_t IR_average_filter(void);
uint16_t IR_game_over(void);

#endif /* IR_DRIVER_ */