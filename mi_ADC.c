
#include "mi_ADC.h"

void init_ADC() {
	ADMUX &= ~(1<<ADLAR); // Resgistro ADC a derecha
	
	ADMUX |= (1<<REFS0); // Voltaje de referencia a 5V
	ADMUX &= ~(1<<REFS1);
	
	ADCSRA |= (7<<ADPS0); // Divisor de frecuencia en 128 (1, 1, 1)
}

int ADC_getData(int canal) {
	ADMUX &= ~(0x0F);
	ADMUX |= (canal<<MUX0); // Pin de ADC seteado segun parametro 'canal' recibido
	
	ADCSRA |= (1<<ADEN); // Habilito conversor ADC
	_delay_us(10);
	
	ADCSRA |= (1<<ADSC); // Comienza la conversion
	
	while (!(ADCSRA & (1<<ADIF))); //Mientras el flag este desactivado, se esta realizando la conversion
	ADCSRA |= (1<<ADIF); // Al terminar la conversion el flag se activa(poniendose en 0), lo desactivo manualmente(poniendole un 1)
	
	ADCSRA &= ~(1<<ADEN); // Deshabilito conversor ADC
	
	return ADC;	
}