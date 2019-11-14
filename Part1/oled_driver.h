/*
 * OLED_driver.h
 *
 * Created: 29.09.2016 14:30:47
 *  Author: Whiskey Dicks
 */ 


#ifndef OLED_DRIVER
#define OLED_DRIVER

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

void oled_init(void);
void oled_printf(char* data, ...);
void oled_inv_printf(char* data, ...);
int oled_put_char(unsigned char);
int oled_inv_put_char(unsigned char c);
int long_string(char* data);
void write_command(uint8_t command);

void oled_goto_letter(int letterPlace);

typedef struct {
	int row, col;
} oled_position_t;

//Recommended functions from the assignment text
void oled_reset(void);
void oled_home(void);
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_clear_line(int line);
void oled_fill_line(int line);
void oled_pos(int row, int column);
#endif 
