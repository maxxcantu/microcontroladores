
#ifndef MOVIMIENTOS_H_
#define MOVIMIENTOS_H_

#include "main.h"
#include "mi_timer1.h"

unsigned int DC1, DC2;

void avanzar(int, int);
void retroceder(int, int);
void detener();
void giro_der(int);
void giro_izq(int);
int comp_vels(int);

#endif /* MOVIMIENTOS_H_ */