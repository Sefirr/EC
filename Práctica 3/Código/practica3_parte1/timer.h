/*
 * timer.h
 *
 *  Created on: 06/05/2014
 *      Author: usuario_local
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "44b.h"
#include "44blib.h"
#include "def.h"
#include "cola.h"

void init_timer();

void timer0_ISR(void) __attribute__ ((interrupt ("IRQ")));

#endif /* TIMER_H_ */
