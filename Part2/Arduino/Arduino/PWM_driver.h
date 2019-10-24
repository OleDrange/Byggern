/*
 * PWM_driver.h
 *
 * Created: 24.10.2019 12:15:20
 *  Author: juliessk
 */ 

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

void PWM_init(float period_sec, unsigned long clock_frequency);

void PWM_set_period(float sec);

void PWM_pulse_set(float sec);


#endif /* PWM_DRIVER_H_ */