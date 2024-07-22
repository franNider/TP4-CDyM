# TP4-CDyM
# Control de un LED RGB con PWM

Este proyecto implementa un control de intensidad y color de un LED RGB utilizando la técnica de PWM (Modulación por Ancho de Pulso). El proyecto ha sido desarrollado como parte del curso "Circuitos Digitales y Microcontroladores (E305)" en la Facultad de Ingeniería de la UNLP.

## Tabla de Contenidos
- [Descripción](#descripción)
- [Requerimientos del Sistema](#requerimientos-del-sistema)
- [Instalación](#instalación)
- [Uso](#uso)
- [Contribución](#contribución)
- [Licencia](#licencia)
- [Autores y Reconocimientos](#autores-y-reconocimientos)

## Descripción

El sistema controla la intensidad y el color de un LED RGB utilizando señales PWM generadas en los terminales PB5, PB2 y PB1 del kit de desarrollo. El proyecto permite seleccionar la proporción de color de cada LED (rojo, verde, azul) y ajustar el brillo mediante un potenciómetro conectado al terminal ADC3.

## Requerimientos del Sistema

El sistema debe cumplir con los siguientes requerimientos:

1. **Generación de PWM**: Generar en los tres terminales de conexión del LED (PB5, PB2 y PB1) señales PWM de frecuencia mayor o igual a 50Hz y con una resolución de 8 bits cada una.
2. **Proporción de Color**: Seleccionar la proporción de color de cada LED (de 0 a 255) para obtener un color resultante.
3. **Interfaz Serie UART0**: Activar mediante comandos enviados por la interfaz serie UART0 cuál proporción de color desea modificar (`R` para rojo, `G` para verde y `B` para azul).
4. **Ajuste de Brillo**: Utilizar el potenciómetro conectado al terminal ADC3 para modificar el brillo del color seleccionado.

## Instalación

### Prerrequisitos
- Kit de desarrollo compatible
- LED RGB ánodo común
- Potenciómetro
- Conexión a una PC vía USB
- Software para terminal serie (por ejemplo, PuTTY)
- Software de simulación Proteus (opcional)

### Pasos
1. Clona el repositorio:
   ```bash
   git clone https://github.com/tu-usuario/control-led-rgb.git
  
