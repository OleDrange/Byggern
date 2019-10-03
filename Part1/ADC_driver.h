/*
 * ADC_driver.h
 *
 * Created: 19.09.2019 10:50:14
 *  Author: juliessk
 */ 



#ifndef ADC_H_
#define ADC_H_

void ADC_init(void);

typedef enum {CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4} ADC_channel;

char ADC_get_data(void);

void ADC_start_read(ADC_channel channel);

#endif /* ADC_H_ */
