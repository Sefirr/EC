/*
 * timer.c
 *
 *  Created on: 06/05/2014
 */

#include "timer.h"

int modo, frecuencia, i;

tCola bufferDisplay;

void init_timer() {

	rI_ISPC = 0xFFFFFFFF;

	rINTMSK &= ~(BIT_GLOBAL|BIT_TIMER0);

	pISR_TIMER0 = (unsigned) timer0_ISR;

	/* Configura el Timer0 */
    rTCFG0 = 255;
    rTCFG1 = 0x0;
    rTCNTB0 = 65535;
    rTCMPB0 = 12800;
    /* establecer update=manual + inverter=on */
	rTCON = 0x2;
	/* inicial timer con auto-reload */
    rTCON  = 0x09;

	rI_ISPC = 0xFFFFFFFF;

	frecuencia = FRECUENCIA_NORMAL;
}

void timer0_ISR() {

	if(modo != MODO_PEDIR) {
		if (modo == MODO_LECTURA) {
			if(i < 4) {
				char aux;
				aux = (bufferDisplay.vector>>(24 - i*8)) & 0xF;

				D8Led_symbol(aux);
				i++;
			} else {
				i = 0;
				modo = MODO_INICIAL;
			}
		} else if (modo == MODO_ESPERA) {
			if(i == 0)  {
				i++;
			} else {
				i = 0;
				modo = MODO_INICIAL;
			}
		}
	}

	rI_ISPC |= BIT_TIMER0;
}
