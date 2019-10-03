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
	
	can_init(MODE_LOOPBACK);
	
	while(1){
		
		//position = joystickPos();
		//position = JoystickDirection();
		//sliderposition = slider_position();
		////int leftbutton = slider_left_button();
		////int rightbutton = slider_right_button();
		//
		//printf("Position of the joystick: \r \n"); 
		//printf("Pos x = %d  ",position.xPos);
		//printf("Pos y = %d  ",position.yPos);
		//printf("Direction = %i \r \n",position.Dir);
		//
		//printf("Position of the sliders: \r \n");
		//printf("Left slider position = %d ", sliderposition.L);
		//printf("Right slider position = %d \r \n\n", sliderposition.R);

		//oled_reset();
		//oled_printf("TESTING");
		//oled_pos(1,0);
		//oled_printf("TESTING1");
		//oled_pos(2,0);
		//oled_printf("TESTING2");
		//oled_pos(3,0);
		//oled_printf("TESTING3");
		//
		//DDRB = 0xFF;
		//oled_init();
		//oled_inv_printf("TESTING");
		//_delay_ms(3000);
		
		//uint16_t test = PORTB;
		//switch_font(FONT_4X6);
		JoystickDir dir = oled_menu_select();
		//oled_menu_print(mymenu);
		
			

			can_message test;
			test.id		= 1337;
			test.data[0]	= 'H';
			test.data[1]	= 'e';
			test.data[2]	= 'l';
			test.data[3]	= 'l';
			test.data[4]	= 'o';
			test.length	= 5;

			can_message test2;
			test2.id		= 1338;
			test2.data[0]	= 'W';
			test2.data[1]	= 'o';
			test2.data[2]	= 'r';
			test2.data[3]	= 'l';
			test2.data[4]	= 'd';
			test2.length	= 5;


			can_message_send(&test);
			can_message_send(&test2);
			
			//printf(" %c ",test.data[0]);

			if ( can_interrupt()){
				test = can_handle_messages();
				
				for(int i = 0; i < 8 ; i++){
					printf(" %c ",test.data[i]);
				}
				printf("\r \n");
			}
		
		_delay_ms(100);
		
		//volatile char *ext_adc = (char *) 0x1400;
		//ext_adc[0] = 0b00000010;
		

	}
	return 0;
}