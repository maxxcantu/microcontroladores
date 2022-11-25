
#include "mi_timer1.h"

void init_timer1() {
	// Modo: FAST PWM - 10bits (TOP=1023)
	TCCR1A |= (1<<WGM10); 
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	
	// Modo 'Clear No Invertido'
	TCCR1A &= ~(1<<COM1A0);
	TCCR1A |= (1<<COM1A1);
	
	TCCR1A &= ~(1<<COM1B0);
	TCCR1A |= (1<<COM1B1);
}

void timer1_on(int _DCA, int _DCB) {
	//Inicializo Timer1 en 0
	TCNT1 = 0x0000; 
	
	// Habilito Timer1 con prescaler = 1
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B &= ~(1<<CS12);	
	
	OCR1A = _DCA; // TOP = 1023 por modo Fast PWM 10bit
	OCR1B = _DCB; //
}

void timer1_off(int _DC) {
	// Deshabilito Timer1 poniendo prescaler en 0
	TCCR1B &= ~(1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B &= ~(1<<CS12);
	
	TCCR1A &= ~(1<<COM1A0);
	TCCR1A &= ~(1<<COM1A1);
	
	TCCR1A &= ~(1<<COM1B0);
	TCCR1A &= ~(1<<COM1B1);
	
	TCNT1 = 0x0000; 
	OCR1A = _DC; 
	OCR1B = _DC;
}