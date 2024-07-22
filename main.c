#define F_CPU 16000000UL  // Define la frecuencia de la CPU como 16 MHz
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "serialPort.h"
#include <stdlib.h>
#include "adc.h"
#define BR9600 (0x67)  // 0x67=103 configura BAUDRATE=9600


volatile char RX_Buffer = 0;     // Buffer para recepción de datos
volatile uint8_t color = 0;      // Variable para almacenar el color seleccionado

uint16_t red_value= 62000;       // Variable para almacenar el valor del color rojo

int main(void)
{
	// Configura los pines PORTB5, PORTB2 y PORTB1 como salidas
	DDRB |= (1 << PORTB5) | (1 << PORTB2) | (1 << PORTB1);
	timer0_init();  // Inicializa el temporizador 0
	timer1_init();  // Inicializa el temporizador 1
	sei();          // Habilita las interrupciones globales

	SerialPort_Init(BR9600); // Inicializa el puerto serie con el baudrate 9600
	SerialPort_TX_Enable();  // Habilita la transmisión por el puerto serie
	SerialPort_RX_Enable();  // Habilita la recepción por el puerto serie
	_delay_ms(100);          // Espera 100 milisegundos

	// Define un mensaje de inicio
	char msg[] = "Introduzca r/R para cambiar la intensidad de rojo, g/G para la de verde, b/B para la de azul. Una vez ajustada la intensidad, presione f/F\n\r";
	SerialPort_Send_String(msg);  // Envía el mensaje de inicio por el puerto serie
	SerialPort_RX_Interrupt_Enable();  // Habilita la interrupción de recepción del puerto serie

	adc_init();  // Inicializa el ADC (Convertidor Analógico-Digital)
	
	uint8_t adc_value;  // Variable para almacenar el valor leído del ADC

	while (1)  // Bucle principal
	{
		if (color == 1) {
			adc_value = adc_read();         // Lee el valor del ADC
			red_value = 255 - adc_value;    // Calcula el nuevo valor de rojo
			setColorRojo(red_value);        // Establece el color rojo con el nuevo valor
		}
		if (color == 2) {
			adc_value = adc_read();         // Lee el valor del ADC
			OCR1B = 255 - adc_value;        // Establece el valor de OCR1B para el color verde
		}
		if (color == 3) {
			adc_value = adc_read();         // Lee el valor del ADC
			OCR1A = 255 - adc_value;        // Establece el valor de OCR1A para el color azul
		}
	}
}

// Interrupción de recepción del USART
ISR (USART_RX_vect){
	RX_Buffer = UDR0;  // Lee el dato recibido del buffer del USART
	if (color == 0) {  // Si no hay color seleccionado
		if (RX_Buffer == 'r' || RX_Buffer == 'R') {  // Si el dato recibido es 'r' o 'R'
			RX_Buffer = 0;  // Limpia el buffer
			color = 1;      // Selecciona el color rojo
		}
		if (RX_Buffer == 'g' || RX_Buffer == 'G') {  // Si el dato recibido es 'g' o 'G'
			RX_Buffer = 0;  // Limpia el buffer
			color = 2;      // Selecciona el color verde
		}
		if (RX_Buffer == 'b' || RX_Buffer == 'B') {  // Si el dato recibido es 'b' o 'B'
			RX_Buffer = 0;  // Limpia el buffer
			color = 3;      // Selecciona el color azul
		}
	}
	if (RX_Buffer == 'f' || RX_Buffer == 'F') {  // Si el dato recibido es 'f' o 'F'
		color = 0;    // Resetea la selección de color
		RX_Buffer = 0;  // Limpia el buffer
	}
}