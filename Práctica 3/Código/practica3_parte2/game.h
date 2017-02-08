/*
 * game.h
 *
 *  Created on: 06/05/2014
 */

#ifndef GAME_H_
#define GAME_H_

#include "cola.h"
#include "44blib.h"
#include "timer.h"
#include "uart.h"

extern tCola buff;

tCola lecturaKeyboard();
tCola lecturaUart();
void game();
char toChar(int n);

#endif /* GAME_H_ */
