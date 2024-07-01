#include "timer.h"
#define PWM_PERIOD 62500   // --- 100%
#define PWM_DELTA 62000    // x---porciento querido
#define PWM_OFF PORTB &= ~(1<<PORTB5);
#define PWM_ON PORTB |= (1<<PORTB5);

void timer1_init(void) {
	TCCR1B |= (1 << WGM12);  // Modo fast PWM 5 , 8 bits, no inv
	TCCR1B |= (1 << CS10); // Prescaler 1
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10); //Modo fast PWM 5, 8 bits, no inv
	OCR1A = 38;  // Valor de comparación para ciclo de trabajo 100 - 14,9% ( azul )
	OCR1B = 137; // Valor de comparacion para ciclo de trabajo 100 - 65,5% ( verde )
}

void timer0_init(void) {											
	TCCR0A |= (1 << WGM01);  // Modo fast PWM 5 , 8 bits, no inv
	TCCR0B |= (1 << CS01) | (1 << CS00); // Prescaler 64
	OCR0A = 249;  
	TIMSK0 |= (1 << OCIE0A);
}

void PWMsoft(){
	static uint16_t PWM_pos = 0;
	if (++PWM_pos >= PWM_PERIOD){
		PWM_pos = 0;
	}
	
	if (PWM_pos < PWM_DELTA){
		PWM_ON;
	}
	else{
		PWM_OFF;
	}
	
	
}

ISR (TIMER0_COMPA_vect){   //llamada cada 1mS
	PWMsoft();

}
