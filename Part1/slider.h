/*
 * slider.h
 *
 * Created: 19.09.2019 14:04:49
 *  Author: juliessk
 */ 
#ifndef SLIDER_H
#define SLIDER_H

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include "ADC_driver.h"

typedef struct {
	uint8_t L;
	uint8_t R;
} slider_str ;


slider_str slider_position(void);
int slider_right_button(void);
int slider_left_button(void);


#endif /* SLIDER_H*/


