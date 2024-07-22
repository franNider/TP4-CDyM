#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

void setColorRojo(uint16_t );
void timer1_init(void);
void timer0_init(void);
void PWMsoft();

#endif /* TIMER_H_ */