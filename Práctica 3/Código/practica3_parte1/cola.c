/*
 * cola.c
 *
 *  Created on: 06/05/2014
 *      Author: usuario_local
 */

#include "cola.h"

void inserta (tCola* cola, char c) {

	cola->elems = ((cola->elems == 4) ? cola->elems : cola->elems +1);
	cola->vector = cola-> vector<<(8) | c;
}

void asigna (tCola* izq, tCola der) {
	izq->vector = der.vector;
	izq->elems = 4;
}

void muestra(tCola cola) {
//pasar el control al timer
	bufferDisplay = cola;
	modo = 1;

	while(modo == 1) {}
}
