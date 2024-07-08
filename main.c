#define F_CPU 16000000UL  // Define la frecuencia de la CPU como 16 MHz
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "serialPort.h"
#include <stdlib.h>
#define BR9600 (0x67)  // 0x67=103 configura BAUDRATE=9600@16MHz

void adc_init();

uint8_t adc_read();

volatile char RX_Buffer = 0;     // Buffer para recepci?n de datos
volatile uint8_t color = 0;

uint16_t red_value= 62000;

int main(void)
{
	DDRB |= (1 << 5) | (1 << 2) | (1 << 1);
	timer0_init();
	timer1_init();
	sei();
	
	SerialPort_Init(BR9600); // Inicializa el puerto serie con el baudrate 9600
	SerialPort_TX_Enable();  // Habilita la transmisi?n por el puerto serie
	SerialPort_RX_Enable();  // Habilita la recepci?n por el puerto serie
	_delay_ms(100);
	//SerialPort_TX_Interrupt_Enable();  // Habilita la interrupci?n de transmisi?n del puerto serie
	char msg[] = "hola\n\r";  // Define un mensaje de inicio
	_delay_ms(500);
	SerialPort_Send_String(msg);  // Envia el mensaje de inicio por el puerto serie
	_delay_ms(500);
	
	SerialPort_RX_Interrupt_Enable();  // Habilita la interrupci?n de recepci?n del puerto serie

	adc_init();
	
	uint8_t adc_value;

	while (1)
	{
		if ( color == 1 ){
			adc_value = adc_read();
			red_value=255 - adc_value;
			setColorRojo(red_value);
		}
		if ( color == 2 ){
			adc_value = adc_read();
			SerialPort_Send_Data(adc_value);
			OCR1B = 255-adc_value;
		}
		if ( color == 3 ){
			adc_value = adc_read();
			SerialPort_Send_Data(adc_value);
			OCR1A = 255-adc_value; 
		}
	}
}

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

ISR (USART_RX_vect){
	RX_Buffer = UDR0;
	if (color == 0){
	if (RX_Buffer == 'r' || RX_Buffer == 'R' ){
		RX_Buffer=0;
		color=1;
	} 
	if (RX_Buffer == 'g' || RX_Buffer == 'G' ){
		RX_Buffer=0;
		color=2;
	}
	if (RX_Buffer == 'b' || RX_Buffer == 'B' ){
		RX_Buffer=0;
		color=3;
	}
	}
	if (RX_Buffer=='f' || RX_Buffer=='F'){
		color=0;
	}
}

ISR (TIMER0_COMPA_vect){   //llamada cada 1mS
	PWMsoft();
}