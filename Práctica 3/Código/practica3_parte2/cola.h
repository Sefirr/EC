/*
 * cola.h
 *
 *  Created on: 06/05/2014
 */

#ifndef COLA_H_
#define COLA_H_

#include "44Blib.h"
#include "timer.h"

extern void D8Led_symbol(int value);

typedef struct {
	int vector;
	unsigned short elems;
} tCola;

extern tCola bufferDisplay;
extern int modo;

void inserta (tCola* cola, char c);

void asigna (tCola* izq, tCola der);

void muestra(tCola cola);

#endif /* COLA_H_ */
