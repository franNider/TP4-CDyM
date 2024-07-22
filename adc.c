#include <avr/io.h> 

void adc_init(){
	ADMUX |= (1 << REFS0);
	ADMUX |= (1 << MUX0) | (1 << MUX1);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADMUX |= (1<<ADLAR);
}

uint8_t adc_read(){
	ADCSRA |= (1 << ADSC);
	while((ADCSRA&(1<<ADIF))==0); //wait for end of conversion
	ADCSRA |= (1<<ADIF); //clear the ADIF flag
	
	return ADCH;
}