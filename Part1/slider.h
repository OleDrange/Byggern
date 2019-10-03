/*
 * slider.h
 *
 * Created: 19.09.2019 14:04:49
 *  Author: juliessk
 */ 

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

typedef struct {
	uint8_t L;
	uint8_t R;
} SLI_pos_t ;


SLI_pos_t slider_position(void);
int slider_right_button(void);
int slider_left_button(void);
