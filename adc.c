#include <avr/io.h> 

// Inicializaci�n del ADC (Convertidor Anal�gico-Digital)
void adc_init(){
	ADMUX |= (1 << REFS0);  // Selecciona la referencia de voltaje AVcc con un capacitor externo en AREF
	ADMUX |= (1 << MUX0) | (1 << MUX1);  // Selecciona el canal de entrada ADC3 (MUX2:0 = 011)
	ADCSRA |= (1 << ADEN);  // Habilita el ADC
	ADCSRA |= (1 << ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Configura el prescaler en 128 (ADPS2:0 = 111)
	ADMUX |= (1<<ADLAR);  // Ajuste a la izquierda del resultado del ADC 
}

// Funci�n para leer el valor del ADC
uint8_t adc_read(){
	ADCSRA |= (1 << ADSC);  // Inicia la conversi�n del ADC
	while((ADCSRA & (1<<ADIF)) == 0); // Espera a que termine la conversi�n 
	ADCSRA |= (1 << ADIF);  // Limpia el flag ADIF escribiendo un 1 en �l
	
	return ADCH;  // Devuelve el byte alto del resultado del ADC
}