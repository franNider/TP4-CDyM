#define F_CPU 16000000UL  // Define la frecuencia de la CPU como 16 MHz
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "serialPort.h"
#include <stdlib.h>
#include "adc.h"
#define BR9600 (0x67)  // 0x67=103 configura BAUDRATE=9600@16MHz


volatile char RX_Buffer = 0;     // Buffer para recepci?n de datos
volatile uint8_t color = 0;

uint16_t red_value= 62000;

int main(void)
{
	DDRB |= (1 << PORTB5) | (1 << PORTB2) | (1 << PORTB1);
	timer0_init();
	timer1_init();
	sei();
	
	SerialPort_Init(BR9600); // Inicializa el puerto serie con el baudrate 9600
	SerialPort_TX_Enable();  // Habilita la transmisi?n por el puerto serie
	SerialPort_RX_Enable();  // Habilita la recepci?n por el puerto serie
	_delay_ms(100);
	char msg[] = "Introduzca r/R para cambiar la intensidad de rojo, g/G para la de verde, b/B para la de azul. Una vez ajustada la intensidad, presione f/F\n\r";  // Define un mensaje de inicio
	SerialPort_Send_String(msg);  // Envia el mensaje de inicio por el puerto serie
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
			OCR1B = 255-adc_value;
		}
		if ( color == 3 ){
			adc_value = adc_read();
			OCR1A = 255-adc_value;
		}
	}
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
		RX_Buffer=0;
	}
}