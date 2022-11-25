
#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define LUZ_MIN 341
#define LUZ_MAX 682
#define LUZ_MIN_MIN 90
#define LUZ_MAX_MAX 900

/* Tabla de verdad driver:
		__________________________________
		| EN | 1A | 2A |     FUNCTION    |
  		|  H |  L |  H | Turn Right      |
		|  H |  H |  L | Turn Left       |
		|  H |  L |  L | Fast motor stop |
		|  H |  H |  H | Fast motor stop |
		|  L |  X |  X | Fast motor stop |
		|____|____|____|_________________| */

#define M1_PWM_OUT (DDRB |= (1<<PINB1)) 
#define M2_PWM_OUT (DDRB |= (1<<PINB2))

/* --- MOTOR 1: PINB4->PINES IN1(1A) ; PINB5->IN2(2A) ; PINB1(OC1A)->EN1(ENA) --- */
// Salida en los pines de Motor1
#define M1_OUT1 (DDRB |= (1<<PINB4))
#define M1_OUT2 (DDRB |= (1<<PINB5))
// Avanza (giro en sentido horario)
#define M1_FWD1 (PORTB &= ~(1<<PINB4)) //Motor1 FOWARD 1/2
#define M1_FWD2 (PORTB |= (1<<PINB5)) //Motor1 FOWARD 2/2
// Retrocede (giro en sentido antihorario)
#define M1_REV1 (PORTB |= (1<<PINB4)) //Motor1 REVERSE 1/2
#define M1_REV2 (PORTB &= ~(1<<PINB5)) //Motor1 REVERSE 2/2
// Detener 
#define M1_OFF1 (PORTB |= (1<<PINB4))
#define M1_OFF2 (PORTB |= (1<<PINB5))

/* --- MOTOR 2: PIND0->IN3(1B) ; PIND1->IN4(2B) ; PINB1(OC1A)->EN1(ENA) --- */
// Salida en los pines de Motor2
#define M2_OUT1 (DDRD |= (1<<PIND0))
#define M2_OUT2 (DDRD |= (1<<PIND1))
//Avanza (giro en sentido antihorario)
#define M2_FWD1 (PORTD |= (1<<PIND0)) //Motor2 FOWARD 1/2
#define M2_FWD2 (PORTD &= ~(1<<PIND1)) //Motor2 FOWARD 2/2
//Retrocede (giro en sentido horario)
#define M2_REV1 (PORTD &= ~(1<<PIND0)) //Motor2 REVERSE 1/2
#define M2_REV2 (PORTD |= (1<<PIND1)) //Motor2 REVERSE 2/2
// Detener
#define M2_OFF1 (PORTD |= (1<<PIND0))
#define M2_OFF2 (PORTD |= (1<<PIND1))

// --- INTERRUPCION PARA CAMBIO DE ESTADO ---
#define ESTADO_IN (DDRD &= ~(1<<PIND2))
#define CFG_INT0_1 (EICRA |= (1<<ISC00))
#define CFG_INT0_2 (EICRA |= (1<<ISC01))
#define CFG_INT0_3 (EIMSK |= (1<<INT0))
#define LED_ACTIVADO_OUT (DDRD |= (1<<PIND3))
#define LED_REPOSO_OUT (DDRD |= (1<<PIND4))
#define LED_ACT_ON (PORTD |= (1<<PIND3))
#define LED_REP_ON (PORTD |= (1<<PIND4))
#define LED_ACT_OFF (PORTD &= ~(1<<PIND3))
#define LED_REP_OFF (PORTD &= ~(1<<PIND4))


volatile unsigned int LUZ_F; //Luz proveniente de sensor LDR Frontal
volatile unsigned int LUZ_D; //Luz proveniente de sensor LDR Derecho
volatile unsigned int LUZ_I; //Luz proveniente de sensor LDR Izquierdo

unsigned int adc_vel; 
unsigned int VELOCIDAD;
unsigned int VEL_GIRO;
unsigned int VELOCIDADx2;

typedef enum {
	DERECHA,
	IZQUIERDA,
	FRONTAL,
	}POSICION_LUZ;
	
typedef enum {
	ACTIVADO,
	REPOSO,
	} ESTADO;
volatile ESTADO estado_actual;

#endif /* MAIN_H_ */