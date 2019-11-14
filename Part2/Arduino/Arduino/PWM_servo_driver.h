/*
 * PWM_servo_driver.h
 *
 * Created: 24.10.2019 13:29:40
 *  Author: juliessk
 */ 
#ifndef SERVO_DRIVER
#define SERVO_DRIVER

void servo_init(unsigned long clock_speed);

void set_servo(int servo_dir);

#endif 