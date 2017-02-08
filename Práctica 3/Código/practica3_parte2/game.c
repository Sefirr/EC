/*
 * game.c
 *
 *  Created on: 06/05/2014
 */

#include "game.h"

extern char key;
extern int modo;

void game() {

	while(1) {
		D8Led_symbol(0xc);

		tCola clave;

		buff.elems = 0;
		clave = lecturaKeyboard();
		muestra(clave);

		tCola intento;

		modo = MODO_INICIAL;

		do {
			D8Led_symbol(0xf);
			Uart_SendString("Introduzca clave:\n");
			//flush buffers
			intento.elems = 0;
			buff.elems = 0;

			intento = lecturaUart();
			if(modo != MODO_PEDIR) {
				muestra(intento);
				if(intento.vector != clave.vector) {
					D8Led_symbol(0xE);
					Uart_SendString("INCORRECTO\n");
					//error
				} else {
					D8Led_symbol(0xA);
					Uart_SendString("CORRECTO\n");
					//acierto
				}
				modo = MODO_ESPERA;
				while (modo == MODO_ESPERA) {}
			}

		} while (modo != MODO_PEDIR);
	}

}

tCola lecturaUart() {
	tCola clave;

	key = '\0';

	while ((key != '\r' || buff.elems < 4)) {
		if(key >= '0' && key < 'f') {
			inserta(&buff, toChar(key));
		}
		key = Uart_Getch();
	}
	asigna(&clave, buff);

	return clave;
}

tCola lecturaKeyboard() {

	tCola clave;

	while (key != 0xF || buff.elems < 4) {
		//lectura por interrupciones
	};

	asigna(&clave, buff);

	return clave;

}

char toChar(int n) {
	char r = -1;
	if(n >= 'a' && n < 'f')
		r = n - 87;
	else if(n >= '0' && n <= '9')
		r = n - 48;

	return r;
}
