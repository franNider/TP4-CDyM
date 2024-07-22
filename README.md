# Trabajo Practico 4 - Circuitos Digitales y Microcontroladores
# Control de un LED RGB con PWM

Este proyecto implementa un control de intensidad y color de un LED RGB utilizando la técnica de PWM (Modulación por Ancho de Pulso), permitiendo modificar la intensidad de cada color con un potenciometro. 
## Tabla de Contenidos
- [Descripción](#descripción)
- [Requerimientos del Sistema](#requerimientos-del-sistema)
- [Requisitos](#requisitos)
- [Autores](#autores)

## Descripción

El sistema controla la intensidad y el color de un LED RGB utilizando señales PWM generadas en los terminales PB5, PB2 y PB1 del kit de desarrollo. El proyecto permite seleccionar la proporción de color de cada LED (rojo, verde, azul) y ajustar el brillo mediante un potenciómetro conectado al terminal ADC3. Se envia por la terminal el color que se desea modificar.

## Requerimientos del Sistema

El sistema debe cumplir con los siguientes requerimientos:

1. **Generación de PWM**: Generar en los tres terminales de conexión del LED (PB5, PB2 y PB1) señales PWM de frecuencia mayor o igual a 50Hz y con una resolución de 8 bits cada una.
2. **Proporción de Color**: Seleccionar la proporción de color de cada LED (de 0 a 255) para obtener un color resultante.
3. **Interfaz Serie UART0**: Activar mediante comandos enviados por la interfaz serie UART0 cuál proporción de color desea modificar (`R` para rojo, `G` para verde y `B` para azul).
4. **Ajuste de Brillo**: Utilizar el potenciómetro conectado al terminal ADC3 para modificar el brillo del color seleccionado.

### Requisitos
- Kit de desarrollo compatible
- LED RGB ánodo común
- Potenciómetro
- Conexión a una PC vía USB
- Software para terminal serie 
- Software de simulación Proteus (opcional)

### Autores
- Melina Caciani Toniolo
- Franco Niderhaus
- Mateo Larsen
