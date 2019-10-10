/*
 * SPI_driver.h
 *
 * Created: 10.10.2019 14:55:32
 *  Author: oledr
 */ 
#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_


void SPI_init();

void SPI_write(char);

char SPI_read(void);

#endif /* SPI_DRIVER_H_ */