/*
 * Byggern.c
 *
 * Created: 19.09.2019 10:43:42
 *  Author: juliessk
 */ 


#include "DriverATmega162.h"
#include "LatchTest.h"
#include "SRAMTestProgram.h"
#include "GalSelect.h"
#include "ADC_driver.h"
#include "SRAM_driver.h"
#include "Joystick_driver.h"
#include "slider.h"
#include "oled_driver.h"
#include "oled_menu.h"
#include "CAN_controller_driver.h"
#include "CAN.h"
long map(long x, long in_min, long in_max, long out_min, long out_max);
int main( )
{
	My_serial_Init ( MYUBRR );
	_delay_ms(1000);
	
	ADC_init();
	SRAM_test();
	Joystick_calibrate();
	Joystick position;
	SLI_pos_t sliderposition;
	oled_init();
	menu* mymenu = oled_menu_init();
	
	can_init(MODE_NORMAL);
	
	
	uint8_t v[2] = {0};
	printf("Rx0 %d  Rx1  %d \n\r",v[0],v[1]);
	while(1){
		
		//SPI_init();
		//
		//mcp_2515_reset();
		//uint8_t val = 10;
		//val = mcp_2515_read(MCP_CANSTAT);
		//printf("val : %d ",val);
		//uint8_t mode_bits = (val & MODE_MASK);
		//mcp_2515_set_mode(MODE_LOOPBACK);
		//_delay_ms(100);
		//val = mcp_2515_read(MCP_CANSTAT);
		//printf("val : %d \n \r",val);
		//uint16_t test = PORTB;
		//switch_font(FONT_4X6);
		//JoystickDir dir = oled_menu_select();
		//oled_menu_print(mymenu);
			can_message dummy;
			can_message dummy1;
			
			can_message hei;

			//can_message test;
			//test.id		= 1337;
			//test.data[0]	= 'H';
			//test.data[1]	= 'e';
			//test.data[2]	= 'l';
			//test.data[3]	= 'l';
			//test.data[4]	= 'o';
			//test.length	= 5;
//
			//can_message test2;
			//test2.id		= 1338;
			//test2.data[0]	= 'W';
			//test2.data[1]	= 'o';
			//test2.data[2]	= 'r';
			//test2.data[3]	= 'l';
			//test2.data[4]	= 'd';
			//test2.length	= 5;
			
			Joystick minJoystick;
			minJoystick = joystickPos();
			minJoystick = JoystickDirection();
			hei.id = 1;
			hei.data[0] = map(minJoystick.xPos,-100,100,0,200);
			hei.data[1] = map(minJoystick.yPos,-100,100,0,200);
			hei.length = 2;

			can_message_send(&hei);
			printf(" Joystick x = %d, Joystick y = %d \r\n",minJoystick.xPos,minJoystick.yPos);
			//
			//can_message_send(&dummy1);
			//if (can_interrupt()){
				//hei = can_handle_messages();
				//
				//for(int i = 0; i < hei.length ; i++){
					//printf(" %c ",hei.data[i]);
				//}
				//printf("\r \n");
			//}
			//can_message_send(&test2);
			//can_message_send(&dummy1);
			//_delay_ms(20);
			////if (can_interrupt()){
				////dummy = can_handle_messages();
				////
				////for(int i = 0; i < dummy.length ; i++){
					////printf(" %c ",dummy.data[i]);
				////}
				////printf("\r \n");
			////}
		
		_delay_ms(1000);
		
		//volatile char *ext_adc = (char *) 0x1400;
		//ext_adc[0] = 0b00000010;
		

	}
	return 0;
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
