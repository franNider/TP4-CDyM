#ifndef ADC_H_
#define ADC_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

void adc_init();
uint8_t adc_read();


#endif /* ADC_H_ */