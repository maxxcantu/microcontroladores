
#include "main.h"
#include "mi_timer1.h"
#include "mi_ADC.h"
#include "movimientos.h"


int main(void)
{
	M1_PWM_OUT; M2_PWM_OUT; 
	M1_OUT1; M1_OUT2;
	M2_OUT1; M2_OUT2;

	// Interrupcion INT0(PD2) para cambiar el ESTADO
	ESTADO_IN;
	CFG_INT0_1; CFG_INT0_2; CFG_INT0_3;
	LED_ACTIVADO_OUT; LED_REPOSO_OUT;	
	
	// Inicializo conversor ADC
	init_ADC();
	
	VEL_GIRO = 750; //750 min para mover motorreductores dc
	
	POSICION_LUZ direccion;
	
	estado_actual = REPOSO;
	
	// Habilito interrupciones globales
	sei(); 
	
    while (1) 
    {
		LUZ_F = ADC_getData(0);
		LUZ_I = ADC_getData(1);
		LUZ_D = ADC_getData(2);

		adc_vel = ADC_getData(5);
		VELOCIDAD = ((adc_vel * 0.51) + 500); // Relacion para que la vel min sea suficiente para superar la friccion de los motores reales
		
		switch (estado_actual) {
			case ACTIVADO:
				LED_ACT_ON;
				LED_REP_OFF;
			
				if (LUZ_D > LUZ_F) {
					direccion = DERECHA; 
				}
				else if (LUZ_I > LUZ_F) {
					direccion = IZQUIERDA; 
				}
				else {
					direccion = FRONTAL; 
				}
		
				//Motor1: Izquierda; Motor2: Derecha
				switch (direccion) {
					case DERECHA: //Girar a Dercha moviendo motor 1
							giro_der(VEL_GIRO);
						break;
			
					case IZQUIERDA: //Girar a Izquierda moveiendo motor 2
							giro_izq(VEL_GIRO);
						break;
				
					case FRONTAL:
						VELOCIDADx2 = comp_vels(VELOCIDAD);
						if (LUZ_F < LUZ_MIN_MIN) {
							avanzar(VELOCIDADx2, VELOCIDADx2);
						}
						else if ((LUZ_F >= LUZ_MIN_MIN) && (LUZ_F <= LUZ_MIN)) {
							avanzar(VELOCIDAD, VELOCIDAD);
						}
						else if ((LUZ_F >= LUZ_MAX) && (LUZ_F <= LUZ_MAX_MAX)) {
							retroceder(VELOCIDAD, VELOCIDAD);
						}
						else if (LUZ_F > LUZ_MAX_MAX) {
							retroceder(VELOCIDADx2, VELOCIDADx2);
						}
						else {
							detener();
						}
						break;
				}
				break;
			
			case REPOSO:
				LED_ACT_OFF;
				LED_REP_ON;
				detener();
				break;
		}
	}
}

ISR(INT0_vect) {
	if (estado_actual == ACTIVADO) {
		estado_actual = REPOSO;
	}
	else if (estado_actual == REPOSO) {
		estado_actual = ACTIVADO;
	}
}
