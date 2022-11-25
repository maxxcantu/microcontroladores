
#include "movimientos.h"

void avanzar(int _VELOCIDAD_A, int _VELOCIDAD_B) { 
	DC2 = _VELOCIDAD_B;
	M1_FWD1; M1_FWD2; 
	M2_FWD1; M2_FWD2; 
	init_timer1();
	timer1_on(DC1, DC2);
}

void retroceder(int _VELOCIDAD_A, int _VELOCIDAD_B) { 
	DC1 = _VELOCIDAD_A;
	DC2 = _VELOCIDAD_B;
	M1_REV1; M1_REV2;
	M2_REV1; M2_REV2;
	init_timer1();
	timer1_on(DC1, DC2);
}

void detener() {
	M1_OFF1; M1_OFF2;
	M2_OFF1; M2_OFF2;
	timer1_off(0);
}

void giro_der(int _VEL_GIRO) {
	DC1 = _VEL_GIRO;
	M1_FWD1; M1_FWD2;
	M2_OFF1; M2_OFF2;
	init_timer1();
	timer1_on(DC1, 0);
}

void giro_izq(int _VEL_GIRO) {
	DC2 = _VEL_GIRO;
	M1_OFF1; M1_OFF2;
	M2_FWD1; M2_FWD2;
	init_timer1();
	timer1_on(0, DC2);
}

int comp_vels(int vel) {
	if (vel <= 800) { //Si la velocidad esta por debajo del 80% de la maxima posible (1023)
		VELOCIDADx2 = 1.25 * vel; //Fijar la velX2 al 25% de vel
	}
	else {
		VELOCIDADx2 = vel; //Lo hago pq ya de por si iria muy rapido y seria perjudicial aumentar aun mas la velx2
	}
	return VELOCIDADx2;
}