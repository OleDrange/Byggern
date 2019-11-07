/*
 * motor_control.h
 *
 * Created: 31.10.2019 13:23:49
 *  Author: juliessk
 */ 

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

typedef enum {LEFT, RIGHT} motor_direction_t;


void motor_init();
void motor_set_direction(motor_direction_t);
void motor_set_speed(uint8_t);
int16_t motor_read_rotation(uint8_t);
void motor_reset_encoder();
void motor_calibrate();
void motor_move(uint8_t speed);

#endif /* MOTOR_DRIVER_H_ */
