/*
 * MCP2515_controlls.h
 *
 * Created: 03.10.2019 15:33:11
 *  Author: oledr
 */ 

#ifndef CAN_CONTROLLER_DRIVER
#define CAN_CONTROLLER_DRIVER

#include <stdint.h>
#include "SPI_driver.h"
#include "MCP2515.h"

uint8_t mcp_2515_init(uint8_t mode);

void mcp_2515_set_mode(uint8_t mode);
void mcp_2515_reset(void);

uint8_t mcp_2515_read(uint8_t address);
void mcp_2515_write(uint8_t address, uint8_t data);

void mcp_2515_request_to_send(char buffer);
void mcp_2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data);
uint8_t mcp_2515_read_status(void);

// Page 63 in the datasheet

#endif /* CAN_CONTROLLER_DRIVER */
