/*
 * timer.h
 *
 *  Created on: 06/05/2014
 */

#ifndef TIMER_H_
#define TIMER_H_

#define MODO_INICIAL 0
#define MODO_LECTURA 1
#define MODO_ESPERA 2
#define MODO_PEDIR 3

#define FRECUENCIA_NORMAL 1
#define FRECUENCIA_RAPIDA 0

#include "44b.h"
#include "44blib.h"
#include "def.h"
#include "cola.h"

void init_timer();

void timer0_ISR(void) __attribute__ ((interrupt ("IRQ")));

#endif /* TIMER_H_ */
