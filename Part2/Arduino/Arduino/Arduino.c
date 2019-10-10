/*
 * Arduino.c
 *
 * Created: 10.10.2019 14:49:57
 *  Author: oledr
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "UART_driver.h"
#include "SPI_driver.h"
#include "CAN_controller_driver.h"
#include "CAN.h"
#include "MCP2515.h"
#define F_CPU 16000000UL
int main(void)
{
	unsigned long clockspeed = F_CPU;
	_delay_ms(20);
	UART_init(clockspeed);
	
	can_init(MODE_NORMAL);

	
    while(1)
    {
		can_message dummy;
		can_message dummy1;
		
		can_message hei;
		
		can_message_send(&dummy1);
		if ( 1){//can_interrupt()){
			hei = can_handle_messages();
			
			for(int i = 0; i < hei.length ; i++){
				printf(" %c ",hei.data[i]);
			}
			printf("\r \n");
		}
	   //printf("test");
	   _delay_ms(10000);
    }
}