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
#include "PWM_driver.h"
#include "PWM_servo_driver.h"
#include "ADC.h"
#include "IR.h"
#define F_CPU 16000000UL

long map(long x, long in_min, long in_max, long out_min, long out_max);

int exersise6(void) {
	while(1)
	{
		can_message dummy;
		can_message dummy1;

		
		//can_message_send(&dummy1);
		//if (can_interrupt()){
		//hei = can_handle_messages();
		//
		//for(int i = 0; i < hei.length ; i++){
		//printf(" %c ",hei.data[i]);
		//}
		//printf("\r \n");
		//}
		can_message hei;
		can_message test;
		//test.id		= 1337;
		//test.data[0]	= 'H';
		//test.data[1]	= 'e';
		//test.data[2]	= 'l';
		//test.data[3]	= 'l';
		//test.data[4]	= 'o';
		//test.length	= 5;

		//can_message test2;
		//test2.id		= 1338;
		//test2.data[0]	= 'W';
		//test2.data[1]	= 'o';
		//test2.data[2]	= 'r';
		//test2.data[3]	= 'l';
		//test2.data[4]	= 'd';
		//test2.length	= 5;

		//can_message_send(&test);
		//can_message_send(&test2);
		if ( can_interrupt()){
			hei = can_handle_messages();
			int xout = map(hei.data[0],0,200,-100,100);
			int yout = map(hei.data[1],0,200,-100,100);
			//for(int i = 0; i < hei.length ; i++){
			printf(" Joystick x = %d, Joystick y = %d ",xout,yout);
			//}
			printf("\r \n");
		}
		//can_message_send(&test2);
		//can_message_send(&dummy1);
		//if ( can_interrupt()){
		//dummy = can_handle_messages();
		//
		//for(int i = 0; i < dummy.length ; i++){
		//printf(" %c ",dummy.data[i]);
		//}
		//printf("\r \n");
		//}
		//printf("test");
		_delay_ms(5000);
	}
}
int main(void)
{
	unsigned long clockspeed = F_CPU;
	_delay_ms(20);
	UART_init(clockspeed);
	
	can_init(MODE_NORMAL);
	PWM_init(0.02, clockspeed);
	printf("NY START!!!!!\r\n");
	servo_init(clockspeed);
	IR_init();
	ADC_init();
	can_message hei;
	int xout;
	int yout;
	while(1)
	{
		
		if ( can_interrupt()){
			hei = can_handle_messages();
			xout = map(hei.data[0],0,200,-100,100);
			yout = map(hei.data[1],0,200,-100,100);
			//for(int i = 0; i < hei.length ; i++){
			printf(" Joystick x = %d, Joystick y = %d ",xout,yout);
			//}
			printf("\r \n");
			
		}
		set_servo(xout);
		
		//
		//printf(" IR sensor = %d, ",IR_game_over());
		//printf("\r \n");
		
		
		_delay_ms(1000);
	}
    
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
