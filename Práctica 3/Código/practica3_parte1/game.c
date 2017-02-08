/*
 * game.c
 *
 *  Created on: 06/05/2014
 *      Author: usuario_local
 */

#include "game.h"

extern char key;
extern int modo;

void game() {

	tCola clave;
	clave = bucleLectura();

	muestra(clave);

	tCola introducida;
	introducida.elems = 0;

	do {
		D8Led_symbol(0xf);

		buff.elems = 0;
		introducida = bucleLectura();
		muestra(introducida);

		introducida.elems = 0;
		if(introducida.vector != clave.vector) {
			D8Led_symbol(0xE);
			//error
			modo = 3;
			while (modo == 3) {}
		} else {
			D8Led_symbol(0xA);
			//acierto
			modo = 3;
			while (modo == 3) {}
		}

	} while (1);

}

tCola bucleLectura() {

	tCola clave;

	while (key != 0xF || buff.elems < 4) {
		//lectura por interrupciones
	};

	asigna(&clave, buff);

	//muestra(clave);

	return clave;
}
