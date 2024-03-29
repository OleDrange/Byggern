
/*
 * CAN_controller_driver.c
 *
 * Created: 10.10.2019 15:34:35
 *  Author: oledr
 */ 
#include "CAN_controller_driver.h"

#include <avr/io.h>
#include <avr/delay.h>

void activate_slave(){
	clear_bit(PORTB, PB7);
}

void deactivate_slave(){
	set_bit(PORTB, PB7);
}

void mcp_2515_set_mode(uint8_t mode){
	mcp_2515_write(MCP_CANCTRL, mode);
}

uint8_t mcp_2515_init(uint8_t mode){
	
	uint8_t val;
	SPI_init();
	
	mcp_2515_reset();
	
	val = mcp_2515_read(MCP_CANSTAT);
	//printf("val : %d ",val);
	uint8_t mode_bits = (val & MODE_MASK);
	if(mode_bits != MODE_CONFIG){
		printf("MCP2515 is NOT in Configuration mode after reset! Its config bits are %x\n", mode_bits);
		return 1;
	}
	
	mcp_2515_set_mode(mode);
	
	val = mcp_2515_read(MCP_CANSTAT);
	mode_bits = (val & MODE_MASK);
	
	if(mode_bits != mode){
		
		printf("MCP2515 is NOT in correct mode after reset! Its config bits are %x\n", mode_bits);
		printf("\n!\n");
		return 1;
	}
	
	
	return 0;
}

void mcp_2515_reset(){
	activate_slave();
	SPI_write(MCP_RESET);
	deactivate_slave();
	_delay_ms(10);	
}

uint8_t mcp_2515_read(uint8_t address){
	activate_slave();
	
	uint8_t data;
	
	SPI_write(MCP_READ);
	SPI_write(address);
	data = SPI_read();
	
	deactivate_slave();
	
	return data;
}


void mcp_2515_write(uint8_t address, uint8_t data) {
	activate_slave();
	
	SPI_write(MCP_WRITE);
	SPI_write(address);
	SPI_write(data);
	
	deactivate_slave();
}

void mcp_2515_request_to_send(char buffer) {
	activate_slave();
	
	SPI_write(buffer);
	
	deactivate_slave();
}

void mcp_2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data) {
	activate_slave();
	
	SPI_write(MCP_BITMOD);
	SPI_write(adress);
	SPI_write(mask);
	SPI_write(data);
	
	deactivate_slave();
}

uint8_t mcp_2515_read_status() {
	activate_slave();
	
	SPI_write(MCP_READ_STATUS);
	uint8_t status = SPI_read();
	
	deactivate_slave();
	
	return status;
}
