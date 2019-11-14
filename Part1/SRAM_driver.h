/*
 * SRAM_driver.h
 *
 * Created: 12.09.2019 15:07:03
 *  Author: oledr
 */ 

#ifndef  SRAM
#define  SRAM

int SRAM_write(uint16_t address, char data);
char SRAM_read(uint16_t address);

#endif
