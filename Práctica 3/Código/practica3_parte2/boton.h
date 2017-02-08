/*
 * boton.h
 *
 *  Created on: 14/05/2014
 *      Author: usuario_local
 */

#ifndef BOTON_H_
#define BOTON_H_

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "def.h"
#include "timer.h"
#include "uart.h"

/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);

#define INTPND  (*(volatile unsigned *)0x01E00004)

#endif /* BOTON_H_ */
