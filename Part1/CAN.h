/*
 * CAN.h
 *
 * Created: 03.10.2019 17:55:02
 *  Author: oledr
 */ 

#ifndef CAN
#define CAN

#include "CAN_controller_driver.h"

typedef struct {
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message;


void can_init(uint8_t mode);
void can_message_send(can_message* message);
uint8_t can_interrupt(void);
can_message can_handle_messages();
int can_error(void);
int can_transmit_complete(int);
void can_message_receive(int, can_message* message);
void can_int_vect(int*);

#endif 
