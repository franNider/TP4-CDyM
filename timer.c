#include "timer.h"
#define PWM_PERIOD 255  // Define el período del PWM como 255 (8 bits)
#define PWM_OFF PORTB &= ~(1<<PORTB5); // Macro para apagar el PWM (poner en bajo el pin PORTB5)
#define PWM_ON PORTB |= (1<<PORTB5);   // Macro para encender el PWM (poner en alto el pin PORTB5)

volatile uint16_t PWM_delta = 100;  // Variable para almacenar el valor de ajuste del PWM

// Inicialización del temporizador 1
void timer1_init(void) {
	TCCR1B |= (1 << WGM12);  // Configura el temporizador 1 en modo Fast PWM 8 bits, no inversor
	TCCR1B |= (1 << CS10);   // Configura el prescaler en 1 (sin división)
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10); // Modo Fast PWM 8 bits, no inversor
	OCR1A = 38;  // Valor de comparación para un ciclo de trabajo de 14,9% (color azul)
	OCR1B = 137; // Valor de comparación para un ciclo de trabajo de 65,5% (color verde)
}

// Inicialización del temporizador 0
void timer0_init(void) {
	TCCR0A |= (1 << WGM01);  // Configura el temporizador 0 en modo CTC (Clear Timer on Compare Match)
	TCCR0B |= (1 << CS01) | (1 << CS00); // Configura el prescaler en 64
	OCR0A = 1;  // Valor de comparación para el temporizador 0
	TIMSK0 |= (1 << OCIE0A); // Habilita la interrupción por comparación del temporizador 0
}

// Función para establecer el valor del color rojo
void setColorRojo(uint16_t red_value) {
	PWM_delta = red_value; // Asigna el valor del color rojo a la variable PWM_delta
}

// Función para manejar el PWM de forma software
void PWMsoft() {
	static uint16_t PWM_pos = 0;  // Variable estática para la posición del PWM
	if (++PWM_pos >= PWM_PERIOD) { // Incrementa la posición del PWM y comprueba si ha alcanzado el período
		PWM_pos = 0;  // Resetea la posición del PWM
	}
	
	if (PWM_pos < PWM_delta) {  // Comprueba si la posición actual está dentro del ciclo de trabajo
		PWM_ON; // Enciende el PWM
		} else {
		PWM_OFF; // Apaga el PWM
	}
}

// Interrupción de comparación del timer0 llamada cada 8uS
ISR (TIMER0_COMPA_vect) {
	PWMsoft();  // Llama a la función PWMsoft() para manejar el PWM
}