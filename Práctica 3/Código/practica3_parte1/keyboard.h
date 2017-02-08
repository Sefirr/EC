#ifndef __keyboard_H__
#define __keyboard_H__

#include "cola.h"

#define KEY_VALUE_MASK	0x0f

void init_keyboard();
char key_read();

void key_ISR(void) __attribute__ ((interrupt ("IRQ")));

#endif /* __keyboard_H__ */
