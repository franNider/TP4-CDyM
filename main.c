/*
 * GccApplication1.c
 *
 * Created: 1/7/2024 14:53:28
 * Author : Barcala
 */ 

#define F_CPU 16000000UL  // Define la frecuencia de la CPU como 16 MHz
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "timer.h"



void PWMsoft();

int main(void)
{
	DDRB |= (1 << 5) | (1 << 2) | (1 << 1);
	
    /* Replace with your application code */
    timer1_init();
	timer0_init();
	sei();
	while (1) 
    {
    }
}


