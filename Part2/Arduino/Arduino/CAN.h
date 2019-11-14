/*
 * CAN.h
 *
 * Created: 10.10.2019 15:34:46
 *  Author: oledr
 */ 

#ifndef CAN
#define CAN

#include "CAN_controller_driver.h"

//typedef enum{
//GAME,
//DIFFICULTY,
//SONG
//} message_type_t;

typedef struct {
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message;


void can_init(uint8_t mode);
void can_message_send(can_message* message);
uint8_t can_interrupt(void);
can_message can_handle_messages();
int can_transmit_complete(int);
void can_message_receive(int, can_message* message);
void can_int_vect(int*);

#endif
