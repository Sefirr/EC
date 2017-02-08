/*
 * timer.c
 *
 *  Created on: 06/05/2014
 *      Author: usuario_local
 */

#include "timer.h"

int modo;
int i;

tCola bufferDisplay;

void init_timer() {
	rINTMOD = 0;

	rI_ISPC = 0xFFFFFFFF;

	rINTMOD=0x0;			/* Inicializamos las interrupciones */
	//rINTMOD |= BIT_TIMER0;

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
}

void timer0_ISR() {
	if (modo == 1) {
		if(i < 4) {
			char aux;
			aux = (bufferDisplay.vector>>(24 - i*8)) & 0xF;

			D8Led_symbol(aux);
			i++;
		} else {
			i = 0;
			modo = 2;
		}
	} else if (modo == 3) {
		if(i == 0)  {
			i++;
		} else {
			i = 0;
			modo = 0;
		}
	}

	rI_ISPC |= BIT_TIMER0;
}
