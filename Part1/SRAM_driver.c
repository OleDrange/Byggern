/*
 * SRAM_driver.c
 *
 * Created: 12.09.2019 15:06:24
 *  Author: oledr
 */ 

#include <stdlib.h>
#include <stdint.h>
#include "SRAM_driver.h"

#ifndef SRAM_FIRST_ADDRESS
#define SRAM_FIRST_ADDRESS 0x1800
#endif

int SRAM_write(uint16_t address, char data){
	if (address > 0x7FF){
		printf("SRAM error, trying to write to an address that is too big\n");
		return EXIT_FAILURE;
	}
	
	volatile char* ext_ram = SRAM_FIRST_ADDRESS;
	ext_ram[address] = data;
	
	return 0;
}

char SRAM_read(uint16_t address){
	if (address > 0x7FF){
		printf("SRAM error, trying to read an address that is too big\n");
		return EXIT_FAILURE;
	}
	
	volatile char* ext_ram = SRAM_FIRST_ADDRESS;
	return ext_ram[address];
	
}
